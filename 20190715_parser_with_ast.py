"""
实现 Compiler P94
program -> block

block -> '{' stmts '}'

stmts -> stmts stmt | e

stmt -> expr ;
    | if ( expr ) stmt
    | while ( expr ) stmt
    | do stmt while ( expr ) ;
    | block

expr -> rel = expr | rel

rel -> rel < add
    | rel <= add
    | add

add -> add + term { Add('+', add.n, term.n) }
    | term

rewrite
add -> term add_rest
add_rest -> + term { Add('+', add.n, term.n) }  add_rest | e

term -> term * factor
    | factor

factor -> ( expr )
    | num
"""
import dataclasses
from dataclasses import dataclass
from enum import IntEnum, auto

import prettyprinter

prettyprinter.install_extras()


class TokenType(IntEnum):
    EOF = auto()
    NUM = auto()
    ID = auto()
    TYPE = auto()
    LEFT_BRACKET = auto()
    RIGHT_BRACKET = auto()
    LEFT_CURLY = auto()
    RIGHT_CURLY = auto()
    EQ = auto()
    LT = auto()
    LTE = auto()
    ADD = auto()
    MINUS = auto()
    COMMA = auto()
    MULTIPLY = auto()
    DIV = auto()
    IF = auto()
    DO = auto()
    WHILE = auto()

    def __repr__(self):
        return self.name

    def __str__(self):
        return self.name


class TokenSymbol:
    EQ = '='
    LT = '<'
    LTE = '<='
    LEFT_BRACKET = '('
    RIGHT_BRACKET = ')'
    LEFT_CURLY = '{'
    RIGHT_CURLY = '}'
    COMMENT = ';'
    MULTIPLY = '*'
    DIV = '/'
    ADD = '+'
    MINUS = '-'


TOKEN_MAP = {
    '(': TokenType.LEFT_BRACKET,
    ')': TokenType.RIGHT_BRACKET,
    '{': TokenType.LEFT_CURLY,
    '}': TokenType.RIGHT_CURLY,
    '+': TokenType.ADD,
    '-': TokenType.MINUS,
    '*': TokenType.MULTIPLY,
    '/': TokenType.DIV,
    ';': TokenType.COMMA,
    '=': TokenType.EQ,
}

KEYWORD_MAP = {
    'if': TokenType.IF,
    'do': TokenType.DO,
    'while': TokenType.WHILE,
}


@dataclasses.dataclass
class Token:
    type: int
    text: str


class Lexer:
    def __init__(self, input: str):
        self.input: str = input
        self.p = 0
        self.line = 1
        self.c = self.input[0]

    def consume(self):
        self.p += 1
        if self.p >= len(self.input):
            self.c = TokenType.EOF
        else:
            self.c = self.input[self.p]

    def match(self, target):
        if self.c != target:
            raise ValueError(f'Expect {target} got {self.c}')
        self.consume()

    def next_token(self):
        while self.c != TokenType.EOF and self.c.isspace():
            if self.c == '\n':
                self.line += 1
            self.consume()
        if self.c == TokenType.EOF:
            return Token(TokenType.EOF, TokenType.EOF)

        if self.c in TOKEN_MAP:
            token = Token(TOKEN_MAP[self.c], self.c)
            self.match(self.c)
            return token

        if self.c == '<':
            self.match('<')
            if self.c == '=':
                self.match('=')
                return Token(TokenType.LTE, '<=')
            return Token(TokenType.LT, '<')

        if self.c.isalpha():
            return self.match_name()
        if self.c.isdigit():
            return self.match_num()
        raise NotImplementedError(f'{self.c} not support')

    def match_name(self):
        result = []
        while self.c != TokenType.EOF and self.c.isalnum():
            result.append(self.c)
            self.consume()
        name = ''.join(result)
        if name in KEYWORD_MAP:
            return Token(KEYWORD_MAP[name], name)
        return Token(TokenType.ID, name)

    def match_num(self):
        result = []
        while self.c != TokenType.EOF and self.c.isdigit():
            result.append(self.c)
            self.consume()
        return Token(TokenType.NUM, ''.join(result))


def test_lexer():
    lexer = Lexer('{ x + y; x <= y; while (i < 0) y = y + 1; }')
    token = lexer.next_token()
    while token.type != TokenType.EOF:
        print(token)
        token = lexer.next_token()


@dataclasses.dataclass
class Node:
    pass


@dataclasses.dataclass
class Expr(Node):
    op: str
    type: int = dataclasses.field(repr=False)


@dataclass
class Eval(Expr):
    expr1: Expr


@dataclasses.dataclass
class Logical(Expr):
    expr1: Expr
    expr2: Expr


@dataclasses.dataclass
class Rel(Logical):
    pass


@dataclass
class Assign(Expr):
    left: Rel
    right: Expr


@dataclasses.dataclass
class Stmt(Node):
    pass


@dataclass
class If(Stmt):
    expr: Expr
    stmt: Stmt


@dataclass
class While(Stmt):
    expr: Expr
    stmt: Stmt


@dataclass
class Do(Stmt):
    expr: Expr
    stmt: Stmt


@dataclass
class Seq(Stmt):
    stmt1: Stmt
    stmt2: Stmt


class Parser:
    def __init__(self, input: Lexer):
        self.input: Lexer = input
        self.lookahead: Token = self.input.next_token()

    def consume(self):
        self.lookahead = self.input.next_token()

    def match(self, target):
        if self.lookahead.type != target:
            raise TypeError(
                f'Expect {repr(target)} got {repr(self.lookahead.type)}')
        self.consume()

    def program(self):
        return self.block()

    def block(self):
        self.match(TokenType.LEFT_CURLY)
        node = self.stmts()
        self.match(TokenType.RIGHT_CURLY)
        return node

    def stmts(self):
        node = None
        if self.lookahead.type in {
            TokenType.IF,
            TokenType.WHILE,
            TokenType.DO,
            TokenType.LEFT_CURLY,
            TokenType.LEFT_BRACKET,
            TokenType.NUM,
            TokenType.ID,
        }:

            node = self.stmt()
            while self.lookahead.type in {
                TokenType.IF,
                TokenType.WHILE,
                TokenType.DO,
                TokenType.LEFT_CURLY,
                TokenType.LEFT_BRACKET,
                TokenType.NUM,
                TokenType.ID,
            }:
                node = Seq(node, self.stmt())
        return node

    def stmt(self):
        if self.lookahead.type in {TokenType.LEFT_BRACKET,
                                   TokenType.NUM, TokenType.ID}:
            node = self.expr()
            self.match(TokenType.COMMA)
            return node
        if self.lookahead.type == TokenType.IF:
            self.match(TokenType.IF)
            self.match(TokenType.LEFT_BRACKET)
            expr = self.expr()
            self.match(TokenType.RIGHT_BRACKET)
            stmt = self.stmt()
            return If(expr, stmt)
        if self.lookahead.type == TokenType.WHILE:
            self.match(TokenType.WHILE)
            self.match(TokenType.LEFT_BRACKET)
            expr = self.expr()
            self.match(TokenType.RIGHT_BRACKET)
            stmt = self.stmt()
            return While(expr, stmt)
        if self.lookahead.type == TokenType.DO:
            self.match(TokenType.DO)
            self.match(TokenType.LEFT_BRACKET)
            expr = self.expr()
            self.match(TokenType.RIGHT_BRACKET)
            stmt = self.stmt()
            return While(expr, stmt)
        if self.lookahead.type == TokenType.LEFT_CURLY:
            return self.block()

    def expr(self):
        node = self.rel()
        if self.lookahead.type != TokenType.EQ:
            return node
        self.match(TokenType.EQ)
        expr = self.expr()
        return Assign('=', TokenType.EQ, node, expr)

    def rel(self):
        """
        rel -> rel < add
            | add
        
        =>
        rel -> add rel_rest
        rel_rest -> < add rel_rest
            | e
        """
        node = self.add()
        while self.lookahead.type in {TokenType.LT, TokenType.LTE}:
            if self.lookahead.type == TokenType.LT:
                self.match(TokenType.LT)
                node = Rel('<', TokenType.LT, node, self.add())
            else:
                self.match(TokenType.LTE)
                node = Rel('<', TokenType.LTE, node, self.add())
        return node

    def add(self):
        node1 = self.term()
        while self.lookahead.type == TokenType.ADD:
            self.match(TokenType.ADD)
            node1 = Rel('+', TokenType.ADD, node1, self.term())

        return node1

    def term(self):
        node = self.factor()
        while self.lookahead.type == TokenType.MULTIPLY:
            self.match(TokenType.MULTIPLY)
            node = Rel('*', TokenType.MULTIPLY, node, self.factor())
        return node

    def factor(self):
        if self.lookahead.type == TokenType.LEFT_BRACKET:
            self.match(TokenType.LEFT_BRACKET)
            node = self.expr()
            self.match(TokenType.RIGHT_BRACKET)
            return node

        if self.lookahead.type == TokenType.ID:
            token = self.lookahead
            self.match(TokenType.ID)
            return token

        token = self.lookahead
        self.match(TokenType.NUM)
        return token


def test_parser():
    content = """
    {
        a = 1;
        b = 1;
        while (a < 3) {
            b = a + b * b;
        }
        if ( b < 10) {
            b = b + 3 ;
        }
    }
"""
    # content = '{ 1 < 2 <= 3;}'

    parser = Parser(Lexer(content))
    root = parser.program()

    def asdict(x):
        d = dict(x)
        if 'op' in d:
            d.pop('type', None)
        elif 'type' in d:
            d['type'] = str(d['type'])
            return d['type'], d['text']
        return d

    # prettyprinter.pprint(dataclasses.asdict(root, dict_factory=asdict))
    prettyprinter.pprint(root)


test_parser()
