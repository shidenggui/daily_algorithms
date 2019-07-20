# coding:utf-8
"""
for Language Implementation Pattern 5 backtracing parser
[a, b = c, [d, e]]

grammars:

array => [ elements ]
elements => element (, element)* | e
element => name
         | name = name
         | array
name => [a-z]+

"""

import unittest
from typing import List

import prettyprinter


import dataclasses
import enum


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


# noinspection PyPep8Naming,PyMethodParameters,PyCallingNonCallable
class Parser:
    def __init__(self, input, size=10):
        self.input: Lexer = input
        self.size = size
        # init pointer
        self.p: int = 0
        # init buffer
        self.lookahead: List[Token] = [None] * self.size

        # fulfill buffer
        for i in range(self.size):
            self.lookahead[i] = self.input.next_token()

        self.parse_tree = None

    def consume(self):
        self.lookahead[self.p % self.size] = self.input.next_token()
        self.p += 1

    def LL(self, k: int):
        return self.lookahead[(self.p + k - 1) % self.size]

    def match(self, target: TokenType):
        if self.LL(1).type != target:
            raise TypeError(f'Expecting {target}, found {self.LL(1).type}')
        self.parse_tree.children.append(Node(target.value, self.LL(1).text))
        self.consume()

    def parse(f):
        def wrapper(self, *args, **kwargs):
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
    def array(self):
        self.match(TokenType.LBRACK)
        self.elements()
        self.match(TokenType.RBRACK)

    @parse
    def elements(self):
        self.element()
        while self.LL(1).type == TokenType.COMMA:
            self.match(TokenType.COMMA)
            self.element()

    @parse
    def element(self):
        if self.LL(1).type == TokenType.LBRACK:
            self.array()
        elif self.LL(1).type == TokenType.NAME and self.LL(2).type == TokenType.EQ:
            self.match(TokenType.NAME)
            self.match(TokenType.EQ)
            self.match(TokenType.NAME)
        elif self.LL(1).type == TokenType.NAME:
            self.match(TokenType.NAME)


class Test(unittest.TestCase):
    def test(self):
        lexer = Lexer('[ a, b = c, [d, e]]')
        token = lexer.next_token()
        while token.type != TokenType.EOF:
            print(token)
            token = lexer.next_token()
        print(token)
        print('parse')
        parser = Parser(Lexer('[ a, b = c, [d, e]]'))
        parser.array()
        Node.print(parser.parse_tree)
