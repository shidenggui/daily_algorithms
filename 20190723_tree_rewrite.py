# coding:utf-8
"""
grammar:

statlist -> stat+
stat -> ID = expr
    | print expr
expr -> mul (+ mul)*
mul -> primary (*|. primary)*
primary -> num
    | id
    | [ expr (, expr)* ]
num -> [0-9]+
"""
import dataclasses
import enum
import unittest
from typing import List

import prettyprinter

prettyprinter.install_extras()


class TokenType(str, enum.Enum):
    EOF = ''
    NUM = 'num'
    ID = 'id'
    MUL = 'mul'
    ADD = 'add'
    DOT = 'dot'
    COMMA = 'comma'
    VEC = 'vec'
    LBRACK = 'LRBACK'
    RBRACK = 'RRBACK'
    EQ = 'eq'
    PRINT = 'print'


TOKEN_MAP = {
    '+': TokenType.ADD,
    '*': TokenType.MUL,
    '[': TokenType.LBRACK,
    ']': TokenType.RBRACK,
    '.': TokenType.DOT,
    ',': TokenType.COMMA,
    '=': TokenType.EQ,
}


@dataclasses.dataclass()
class Token:
    type: str
    text: str


# noinspection PyShadowingBuiltins
class Lexer:
    def __init__(self, input: str):
        self.input = input
        self.p = -1
        self.c = ''
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
        if self.c == TokenType.EOF:
            return Token(TokenType.EOF, '')

        while self.c.isspace():
            self.consume()
        if self.c in TOKEN_MAP:
            token = Token(TOKEN_MAP[self.c], self.c)
            self.consume()
            return token

        if self.c.isdigit():
            return self.match_num()

        if self.c.isalpha():
            token = self.match_id()
            if token.text == TokenType.PRINT:
                return Token(TokenType.PRINT, TokenType.PRINT)
            return token
        raise TypeError(f'Un expected char {self.c}')

    def match_id(self):
        id = []
        while self.c.isalnum():
            id.append(self.c)
            self.consume()
        return Token(TokenType.ID, ''.join(id))

    def match_num(self):
        num = []
        while self.c.isdigit():
            num.append(self.c)
            self.consume()
        return Token(TokenType.NUM, ''.join(num))


@dataclasses.dataclass()
class Node:
    token: Token

    def walk(self):
        pass


@dataclasses.dataclass()
class IntNode(Node):

    def walk(self):
        print(self.token.text, end='')


@dataclasses.dataclass()
class IdNode(Node):

    def walk(self):
        print(self.token.text, end='')


@dataclasses.dataclass()
class AddNode(Node):
    left: Node
    right: Node

    def walk(self):
        self.left.walk()
        self.right.walk()
        print(self.token.text, end='')


@dataclasses.dataclass()
class MulNode(Node):
    left: Node
    right: Node

    def walk(self):
        self.left.walk()
        self.right.walk()
        print(self.token.text, end='')


@dataclasses.dataclass()
class VecNode(Node):
    children: List[Node]

    def walk(self):
        print('[ ', end='')
        for child in self.children:
            child.walk()
            print(', ', end='')
        print('] ', end='')


@dataclasses.dataclass()
class DotNode(Node):
    left: Node
    right: Node

    def walk(self):
        self.left.walk()
        print(self.token.text, end='')
        self.right.walk()


@dataclasses.dataclass()
class EqNode(Node):
    left: Node
    right: Node

    def walk(self):
        self.left.walk()
        print(self.token.text, end='')
        self.right.walk()


@dataclasses.dataclass()
class PrintNode(Node):
    expr: Node

    def walk(self):
        print('print ', end='')
        self.expr.walk()


class PrintVisitor:
    def visit(self, node):
        func = getattr(self, f'visit_{node.token.type}')
        func(node)

    def visit_add(self, node: AddNode):
        self.visit(node.left)
        print(' + ', end='')
        self.visit(node.right)

    def visit_mul(self, node: MulNode):
        if node.left.token.type != TokenType.NUM:
            print('(', end='')

        self.visit(node.left)

        if node.left.token.type != TokenType.NUM:
            print(')', end='')
        print(' * ', end='')
        if node.right.token.type != TokenType.NUM:
            print('(', end='')

        self.visit(node.right)
        if node.right.token.type != TokenType.NUM:
            print(')', end='')


    def visit_eq(self, node: EqNode):
        self.visit(node.left)
        print(' = ', end='')
        self.visit(node.right)

    def visit_dot(self, node: EqNode):
        self.visit(node.left)
        print('.', end='')
        self.visit(node.right)

    def visit_num(self, node: IntNode):
        print(node.token.text, end='')

    def visit_id(self, node: IdNode):
        print(node.token.text, end='')

    def visit_vec(self, node: VecNode):
        print('[', end='')
        first = True
        for child in node.children:
            if first:
                first = False
            else:
                print(', ', end='')
            self.visit(child)
        print('] ', end='')
        # print(node.token.text, end='')


def op_token(op):
    return Token(TOKEN_MAP[op], op)


class RewriteVisitor:
    def visit(self, node):
        func = getattr(self, f'visit_{node.token.type}')
        return func(node)

    def visit_add(self, node: AddNode):
        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        return node

    def visit_mul(self, node: MulNode):

        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        # 这个操作下面有更加优化版本
        if (node.left.token.type == TokenType.NUM and
                node.right.token.type == TokenType.VEC):
            new_vec = VecNode(Token(TokenType.VEC, 'vec'), [])

            for child in node.right.children:
                mul_node = MulNode(op_token('*'), node.left, child)
                new_vec.children.append(mul_node)
            return new_vec
        if (
                node.left.token.type == TokenType.NUM and node.left.token.text == '0'):
            return node.left
        if (
                node.right.token.type == TokenType.NUM and node.right.token.text == '0'):
            return node.right

        return node

    def visit_eq(self, node: EqNode):
        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        return node

    def visit_dot(self, node: EqNode):
        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        return node

    def visit_num(self, node: IntNode):
        return node

    def visit_id(self, node: IdNode):
        return node

    def visit_vec(self, node: VecNode):
        for i, child in enumerate(node.children):
            node.children[i] = self.visit(child)
        return node
        # print(node.token.text, end='')


class Rewrite2Visitor:
    def visit(self, node):
        func = getattr(self, f'visit_{node.token.type}')
        return func(node)

    def visit_add(self, node: AddNode):
        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        if (
                node.left.token.type == TokenType.NUM and node.right.token.type == TokenType.NUM):
            if node.left.token.text == node.right.token.text:
                return MulNode(op_token('*'),
                               left=node.left,
                               right=IntNode(Token(TokenType.NUM, '2'))
                               )
        return node

    def visit_mul(self, node: MulNode):
        if (node.left.token.type == TokenType.NUM and
                node.right.token.type == TokenType.VEC):
            new_vec = VecNode(Token(TokenType.VEC, 'vec'), [])

            for child in node.right.children:
                mul_node = MulNode(op_token('*'), node.left, child)
                new_vec.children.append(mul_node)

            for i, mul_node in enumerate(new_vec.children):
                new_vec.children[i] = self.visit(mul_node)
            return new_vec

        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        if (
                node.left.token.type == TokenType.NUM and node.left.token.text == '0'):
            return node.left
        if (
                node.right.token.type == TokenType.NUM and node.right.token.text == '0'):
            return node.right

        return node

    def visit_eq(self, node: EqNode):
        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        return node

    def visit_dot(self, node: EqNode):
        node.left = self.visit(node.left)
        node.right = self.visit(node.right)
        return node

    def visit_num(self, node: IntNode):
        return node

    def visit_id(self, node: IdNode):
        return node

    def visit_vec(self, node: VecNode):
        for i, child in enumerate(node.children):
            node.children[i] = self.visit(child)
        return node
        # print(node.token.text, end='')


class Parser:
    def __init__(self, input: Lexer, size: int):
        self.input = input
        self.size = size
        self.p = 0
        self.lookahead: List[Token] = [None] * self.size

        for i in range(size):
            self.lookahead[i] = self.input.next_token()

    def consume(self):
        self.lookahead[self.p] = self.input.next_token()
        self.p = (self.p + 1) % self.size

    def LL(self, k: int):
        return self.lookahead[(self.p + k - 1) % self.size]

    def match(self, target: str):
        if self.LL(1).type != target:
            raise TypeError(f'Expecting {target}, found {self.LL(1).type}')

        self.consume()

    def stat(self):
        if self.LL(1).type == TokenType.ID:
            id_node = self.id()
            eq_token = self.LL(1)
            self.match(TokenType.EQ)
            return EqNode(eq_token, id_node, self.expr())
        elif self.LL(1).type == TokenType.PRINT:
            print_token = self.LL(1)
            self.match(TokenType.PRINT)
            return PrintNode(print_token, self.expr())
        raise TypeError

    def expr(self):
        node = self.mul()
        while self.LL(1).type == TokenType.ADD:
            self.match(TokenType.ADD)
            node = AddNode(Token(TokenType.ADD, '+'), node, self.mul())
        return node

    def mul(self):
        node = self.primary()

        type_map = {
            TokenType.MUL: MulNode,
            TokenType.DOT: DotNode,
        }
        # while self.LL(1).type == TokenType.COMMA:
        while self.LL(1).type in {TokenType.MUL, TokenType.DOT}:
            op_token = self.LL(1)
            self.match(self.LL(1).type)
            node = type_map[op_token.type](op_token, node, self.primary())
        return node

    def primary(self):
        if self.LL(1).type == TokenType.NUM:
            return self.num()
        if self.LL(1).type == TokenType.ID:
            return self.id()
        if self.LL(1).type == TokenType.LBRACK:
            self.match(TokenType.LBRACK)
            node = VecNode(Token(TokenType.VEC, 'vec'), [])
            node.children.append(self.expr())
            while self.LL(1).type == TokenType.COMMA:
                self.match(TokenType.COMMA)
                node.children.append(self.expr())
            self.match(TokenType.RBRACK)
            return node

    def num(self):
        token = IntNode(self.LL(1))
        self.match(TokenType.NUM)
        return token

    def id(self):
        token = IdNode(self.LL(1))
        self.match(TokenType.ID)
        return token


class Test(unittest.TestCase):
    def test(self):
        lexer = Lexer('a = [1, 2] . [3, 4]')
        token = lexer.next_token()
        while token.type != TokenType.EOF:
            print(token)
            token = lexer.next_token()
        print(token)

    def test_parser(self):
        lexer = Lexer('4 * [0, 5 * 0, 3, 4 + 4 + 8]')
        parser = Parser(lexer, 10)
        ast = parser.expr()
        # prettyprinter.cpprint(dataclasses.asdict(ast))
        print('old ast')
        PrintVisitor().visit(ast)
        print()
        new_ast = Rewrite2Visitor().visit(ast)
        print('\noptimize: iter 1')
        PrintVisitor().visit(new_ast)
        print('\noptimize: iter 2')
        new_ast = Rewrite2Visitor().visit(new_ast)
        PrintVisitor().visit(new_ast)
        # prettyprinter.pprint(ast)
        # ast.walk()
        # PrintVisitor().visit(ast)
