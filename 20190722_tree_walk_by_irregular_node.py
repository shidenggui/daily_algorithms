# coding:utf-8
"""
grammar:

expr -> mul (+ mul)*
mul -> num (* num)*
num -> [0-9]+
"""
import dataclasses
import enum
import unittest
from typing import List

import prettyprinter


class TokenType(str, enum.Enum):
    EOF = ''
    NUM = 'num'
    MUL = 'mul'
    ADD = 'add'


@dataclasses.dataclass()
class Token:
    type: str
    text: str


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

        if self.c == '+':
            token = Token(TokenType.ADD, '+')
        elif self.c == '*':
            token = Token(TokenType.MUL, '*')
        elif self.c.isdigit():
            token = self.match_num()
        else:
            raise TypeError(f'Un expected char {self.c}')
        self.consume()
        return token

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

    def match(self, target: TokenType):
        if self.LL(1).type != target:
            raise TypeError(f'Expecting {target}, found {self.LL(1).type}')

        self.consume()

    def expr(self):
        node = self.mul()
        while self.LL(1).type == TokenType.ADD:
            self.match(TokenType.ADD)
            node = AddNode(Token(TokenType.ADD, '+'), node, self.mul())
        return node

    def mul(self):
        node = self.num()
        while self.LL(1).type == TokenType.MUL:
            self.match(TokenType.MUL)
            node = MulNode(Token(TokenType.MUL, '*'), node, self.num())
        return node

    def num(self):
        token = IntNode(self.LL(1))
        self.match(TokenType.NUM)
        return token


class Test(unittest.TestCase):
    def test(self):
        lexer = Lexer('1 + 2 * 3')
        token = lexer.next_token()
        while token.type != TokenType.EOF:
            print(token)
            token = lexer.next_token()
        print(token)

    def test_parser(self):
        lexer = Lexer('1 + 2 * 3 + 4')
        parser = Parser(lexer, 10)
        ast = parser.expr()
        prettyprinter.cpprint(dataclasses.asdict(ast))
        ast.walk()
