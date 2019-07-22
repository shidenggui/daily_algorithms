# coding:utf-8
"""
for Language Implementation Pattern 5 backtracking parser and 6 memory
support
[a, b] = [c, d]

grammars:

stat => array EOF
    | array = array
array => [ elements ]
elements => element (, element)* | e
element => name
         | name = name
         | array
name => [a-z]+

"""
import pyhanlp

import collections
import dataclasses
import enum
import functools
import unittest
from typing import List


class TokenType(str, enum.Enum):
    LBRACK = '['
    RBRACK = ']'
    COMMA = ','
    EQ = '='
    EOF = '`'
    NAME = 'name'


@dataclasses.dataclass()
class Token:
    type: TokenType
    text: str


# noinspection PyShadowingBuiltins
class Lexer:
    def __init__(self, input):
        # input string
        self.input = input
        # pointer to input
        self.p = -1
        # char under pointer
        self.c: str = None
        self.consume()

    def consume(self):
        self.p += 1
        if self.p >= len(self.input):
            self.c = TokenType.EOF
        else:
            self.c = self.input[self.p]

    def match(self, target):
        if self.c != target:
            raise TypeError(f'Expecting {target}, found {self.c}')
        self.consume()

    def next_token(self):
        # if eof return directly
        if self.c == TokenType.EOF:
            return Token(TokenType.EOF, TokenType.EOF.value)

        # skip ws
        while self.c.isspace():
            self.consume()

        # match token
        if self.c in '[],=':
            token = Token(TokenType(self.c), self.c)
            self.match(self.c)
            return token

        # match name
        if self.c.isalpha():
            return self.match_name()

        return Token(TokenType.EOF, TokenType.EOF.value)

    def match_name(self):
        name = []
        while self.c.isalpha():
            name.append(self.c)
            self.consume()
        return Token(TokenType.NAME, ''.join(name))


@dataclasses.dataclass()
class Node:
    type: str
    text: str = dataclasses.field(default=None)
    children: List['Node'] = dataclasses.field(default_factory=list)

    @classmethod
    def print(cls, root, layer=0):
        if root is None:
            return
        print(' ' * layer * 10, f'{root.type}:{root.text}')
        for child in root.children:
            cls.print(child, layer + 1)


@dataclasses.dataclass()
class AstNode:
    token: Token
    children: List['AstNode'] = dataclasses.field(default_factory=list)

    @classmethod
    def print(cls, root, layer=0):
        if root is None:
            return
        print(' ' * layer * 10, root.token)
        for child in root.children:
            cls.print(child, layer + 1)


# noinspection PyPep8Naming,PyMethodParameters,PyCallingNonCallable
class Parser:
    def __init__(self, input):
        self.input: Lexer = input
        # init pointer
        self.p: int = 0
        # init buffer
        self.lookahead: List[Token] = [self.input.next_token()]

        # init marker
        self.markers = []

        # init cache
        self.cache = collections.defaultdict(dict)

        self.parse_tree = None

    def sync(self, k):
        while len(self.lookahead) < (self.p + k):
            self.lookahead.append(self.input.next_token())

    def is_speculate(self):
        return bool(self.markers)

    def consume(self):
        self.p += 1
        # hit end
        if self.p == len(self.lookahead) and not self.is_speculate():
            self.p = 0
            self.lookahead.clear()
            self.cache.clear()
        self.sync(1)

    def LL(self, k: int):
        self.sync(k)
        return self.lookahead[self.p + k - 1]

    def match(self, target: TokenType):
        if self.LL(1).type != target:
            raise TypeError(f'Expecting {target}, found {self.LL(1).type}')
        if not self.is_speculate():
            self.parse_tree.children.append(Node(target.value, self.LL(1).text))
        self.consume()

    def mark(self):
        self.markers.append(self.p)

    def release(self):
        self.p = self.markers.pop()

    def parse(f):
        @functools.wraps(f)
        def wrapper(self, *args, **kwargs):
            if self.is_speculate():
                return f(self, *args, **kwargs)
            node = Node(f.__name__)
            if self.parse_tree is None:
                self.parse_tree = node
            else:
                self.parse_tree.children.append(node)

            saved = self.parse_tree
            self.parse_tree = node
            result = f(self, *args, **kwargs)
            self.parse_tree = saved
            return result

        return wrapper

    @parse
    def stat(self):
        if self.speculate_array_eof():
            return self.array()
        elif self.speculate_array_eq_array():
            left_node = self.array()
            eq_node = AstNode(self.LL(1))
            self.match(TokenType.EQ)
            right_node = self.array()
            eq_node.children.append(left_node)
            eq_node.children.append(right_node)
            return eq_node
        else:
            raise TypeError(f'Matching state error: {self.LL(1)}')

    def speculate(f):
        def wrapper(self, *args, **kwargs):
            self.mark()
            try:
                f(self, *args, **kwargs)
            except TypeError:
                return False
            finally:
                self.release()
            return True

        return wrapper

    @speculate
    def speculate_array_eof(self) -> bool:
        self.array()
        self.match(TokenType.EOF)

    @speculate
    def speculate_array_eq_array(self):
        self.array()
        self.match(TokenType.EQ)
        self.array()

    def memorize(f):
        @functools.wraps(f)
        def wrapper(self, *args, **kwargs):
            rule_cache = self.cache[f.__name__]
            start_token_index = self.p
            if self.is_speculate() and self.already_parse_rule(rule_cache):
                self.p = rule_cache[self.p]
                return
            try:
                result = f(self, *args, **kwargs)
            except TypeError:
                if self.is_speculate():
                    rule_cache[start_token_index] = -1
                raise
            else:
                if self.is_speculate():
                    rule_cache[start_token_index] = self.p
            return result

        return wrapper

    def already_parse_rule(self, rule_cache):
        if self.p not in rule_cache:
            return False
        if rule_cache[self.p] == -1:
            raise TypeError('Previous parse error')
        return True

    @parse
    @memorize
    def array(self):
        self.match(TokenType.LBRACK)
        node = self.elements()
        self.match(TokenType.RBRACK)
        return node

    @parse
    @memorize
    def elements(self):
        node = AstNode(Token('list', ''))
        node.children.append(self.element())
        while self.LL(1).type == TokenType.COMMA:
            self.match(TokenType.COMMA)
            node.children.append(self.element())
        return node

    @parse
    @memorize
    def element(self):
        if self.LL(1).type == TokenType.LBRACK:
            return self.array()
        elif self.LL(1).type == TokenType.NAME and self.LL(
                2).type == TokenType.EQ:
            eq_node = AstNode(Token(TokenType.EQ, TokenType.EQ.value), )
            eq_node.children.append(AstNode(self.LL(1)))
            self.match(TokenType.NAME)
            self.match(TokenType.EQ)
            eq_node.children.append(AstNode(self.LL(1)))
            self.match(TokenType.NAME)
            return eq_node
        elif self.LL(1).type == TokenType.NAME:
            node = AstNode(self.LL(1))
            self.match(TokenType.NAME)
            return node
        else:
            raise TypeError(f'Cant parser element for {self.LL(1)}')


class Test(unittest.TestCase):
    def test(self):
        lexer = Lexer('[[ a, b = c, [d, e]]')
        token = lexer.next_token()
        while token.type != TokenType.EOF:
            print(token)
            token = lexer.next_token()
        print(token)
        print('parse')
        parser = Parser(Lexer('[a, b]  = [ c, d] '))
        ast = parser.stat()
        Node.print(parser.parse_tree)
        print('ast')
        AstNode.print(ast)
