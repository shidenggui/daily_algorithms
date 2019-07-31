# coding:utf-8
"""
grammar:

statlist -> (assign|vec_dec|call_func|func_dec|block)+
func_dec -> type id '(' (type id)* ')' block
call_func -> id '(' (type id)* ')' ;
block -> { statlist ('return' primary;)? }
assign -> id = expr;
var_dec -> type id (= expr)? ;

expr -> primary (+ primary)*
primary -> id
    | num
    | ( expr )
id -> [a-zA-Z]\w*
num -> [0-9]+
type -> float int

"""
import dataclasses
import enum
import functools
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
    LBRACK = 'lrback'
    RBRACK = 'rrback'
    EQ = 'eq'
    PRINT = 'print'
    SEMI = 'semicolon'
    TYPE = 'type'
    CLASS = 'class'
    RETURN = 'return'
    LCURLY = 'lcurly'
    RCURLY = 'rcurly'
    # virtual type
    VAR_DECL = 'var_decl'
    METHOD_DECL = 'method_decl'
    FUNC_DECL = 'func_decl'
    STATLIST = 'statlist'
    METHOD = 'method'
    PARAMETER = 'parameter'
    EXPR = 'expr'
    CALL_FUNC = 'call_func'
    BLOCK = 'block'
    RETURN_NODE = 'return_node'


@dataclasses.dataclass()
class Token:
    type: str
    text: str
    line: int = dataclasses.field(default=0)


def virtual_token(type, line):
    return Token(type, type, line)


TYPE_TOKEN = {'float', 'int', 'void'}

TOKEN_MAP = {
    '+': TokenType.ADD,
    '*': TokenType.MUL,
    '(': TokenType.LBRACK,
    ')': TokenType.RBRACK,
    '{': TokenType.LCURLY,
    '}': TokenType.RCURLY,
    '.': TokenType.DOT,
    ',': TokenType.COMMA,
    '=': TokenType.EQ,
    ';': TokenType.SEMI,
}

KEYWORDS_MAP = {
    'print': TokenType.PRINT,
    'return': TokenType.RETURN,
    'class': TokenType.CLASS,
    'float': TokenType.TYPE,
    'int': TokenType.TYPE,
    'void': TokenType.TYPE,
}


# OP_TOKEN = {op: Token(type, op) for op, type in TOKEN_MAP.items()}


# noinspection PyShadowingBuiltins
class Lexer:
    def __init__(self, input: str):
        self.input = input
        self.p = -1
        self.c = ''
        self.consume()
        self.line = 1

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
        while self.c.isspace():
            if self.c == '\n':
                self.line += 1
            self.consume()
        if self.c == TokenType.EOF:
            return Token(TokenType.EOF, '', self.line)

        if self.c in TOKEN_MAP:
            token = Token(TOKEN_MAP[self.c], self.c, self.line)
            self.consume()
            return token

        if self.c.isdigit():
            return self.match_num()

        if self.c.isalpha():
            token = self.match_id()
            if token.text in KEYWORDS_MAP:
                return Token(KEYWORDS_MAP[token.text], token.text, self.line)
            return token
        raise TypeError(f'Un expected char <{self.c}>')

    def match_id(self):
        id = []
        while self.c.isalnum():
            id.append(self.c)
            self.consume()
        return Token(TokenType.ID, ''.join(id), self.line)

    def match_num(self):
        num = []
        while self.c.isdigit():
            num.append(self.c)
            self.consume()
        return Token(TokenType.NUM, ''.join(num), self.line)


@dataclasses.dataclass()
class Node:
    token: Token
    children: List['Node']


@dataclasses.dataclass()
class IntNode(Node):
    pass


@dataclasses.dataclass()
class IdNode(Node):
    pass


@dataclasses.dataclass()
class StatListNode(Node):
    pass


@dataclasses.dataclass()
class VarDeclNode(Node):
    pass


@dataclasses.dataclass()
class ExprlNode(Node):
    pass


@dataclasses.dataclass()
class AddNode(Node):
    pass


@dataclasses.dataclass()
class MethodNode(Node):
    pass


@dataclasses.dataclass()
class ParameterNode(Node):
    pass


@dataclasses.dataclass()
class BlockNode(Node):
    pass


@dataclasses.dataclass()
class LocalDeclNode(Node):
    pass


@dataclasses.dataclass()
class AssignNode(Node):
    pass


@dataclasses.dataclass()
class CallFuncNode(Node):
    pass


@dataclasses.dataclass()
class FuncDeclNode(Node):
    pass


@dataclasses.dataclass()
class BlockNode(Node):
    pass


@dataclasses.dataclass()
class BlocklNode(Node):
    pass


class PrintVistor:
    def __init__(self):
        self.indent = 0

    def incr_indent(self):
        self.indent += 4

    def decr_indent(self):
        self.indent -= 4

    def print(self, node):
        type = node.token.type

        func = getattr(self, f'print_{type}', None)
        if func:
            func(node)
        else:
            self.default_print(node)

    def print_var_decl(self, node: Node):
        print(' ' * self.indent, end='')
        self.print(node.children[0])

        print(' ', end='')
        self.print(node.children[1])

        if len(node.children) > 2:
            print(' = ', end='')
            for child in node.children[2:]:
                self.print(child)
            # self.print(node.children[2])
        print(';')

    def print_block(self, node: Node):
        print(' ' * self.indent + '{')
        self.incr_indent()
        for child in node.children:
            self.print(child)
        self.decr_indent()
        print(' ' * self.indent + '}')

    def print_func_decl(self, node: Node):
        self.print(node.children[0])
        print(' ', end='')
        for child in node.children[1:]:
            self.print(child)

    def print_return_node(self, node: Node):
        print(self.indent * ' ', end='')
        print('return ', end='')
        for child in node.children:
            self.print(child)
        print(';')

    def print_call_func(self, node: Node):
        print(self.indent * ' ', end='')
        self.print(node.children[0])
        print('(', end='')
        self.print(node.children[1])
        for child in node.children[2:]:
            print(', ', end='')
            self.print(child)
        print(')', end='')
        print(';')

    def print_parameter(self, node: Node):
        print('(', end='')
        it = iter(node.children)
        if node.children:
            self.print(next(it))
            print(' ', end='')
            self.print(next(it))
        for child in it:
            print(', ', end='')
            self.print(child)
            print(' ', end='')
            self.print(next(it))
        print(')', end='')

    def print_id(self, node):
        print(node.token.text, end='')

    def print_num(self, node):
        print(node.token.text, end='')

    def print_type(self, node):
        print(node.token.text, end='')

    def default_print(self, node):
        for child in node.children:
            self.print(child)

    def print_add(self, node: Node):
        print(end='')
        self.print(node.children[0])
        print(' + ', end='')
        self.print(node.children[1])

    def print_eq(self, node: Node):
        print(' ' * self.indent, end='')
        self.print(node.children[0])
        print(' = ', end='')
        self.print(node.children[1])
        print(';')

class ScopeVistor:
    def __init__(self):
        self.indent = 0

    def incr_indent(self):
        self.indent += 4

    def decr_indent(self):
        self.indent -= 4

    def print(self, node):
        type = node.token.type

        func = getattr(self, f'print_{type}', None)
        if func:
            func(node)
        else:
            self.default_print(node)

    def print_var_decl(self, node: Node):
        print(' ' * self.indent, end='')
        self.print(node.children[0])

        print(' ', end='')
        self.print(node.children[1])

        if len(node.children) > 2:
            print(' = ', end='')
            for child in node.children[2:]:
                self.print(child)
            # self.print(node.children[2])
        print(';')

    def print_block(self, node: Node):
        print(' ' * self.indent + '{')
        self.incr_indent()
        for child in node.children:
            self.print(child)
        self.decr_indent()
        print(' ' * self.indent + '}')

    def print_func_decl(self, node: Node):
        self.print(node.children[0])
        print(' ', end='')
        for child in node.children[1:]:
            self.print(child)

    def print_return_node(self, node: Node):
        print(self.indent * ' ', end='')
        print('return ', end='')
        for child in node.children:
            self.print(child)
        print(';')

    def print_call_func(self, node: Node):
        print(self.indent * ' ', end='')
        self.print(node.children[0])
        print('(', end='')
        self.print(node.children[1])
        for child in node.children[2:]:
            print(', ', end='')
            self.print(child)
        print(')', end='')
        print(';')

    def print_parameter(self, node: Node):
        print('(', end='')
        it = iter(node.children)
        if node.children:
            self.print(next(it))
            print(' ', end='')
            self.print(next(it))
        for child in it:
            print(', ', end='')
            self.print(child)
            print(' ', end='')
            self.print(next(it))
        print(')', end='')

    def print_id(self, node):
        print(node.token.text, end='')

    def print_num(self, node):
        print(node.token.text, end='')

    def print_type(self, node):
        print(node.token.text, end='')

    def default_print(self, node):
        for child in node.children:
            self.print(child)

    def print_add(self, node: Node):
        print(end='')
        self.print(node.children[0])
        print(' + ', end='')
        self.print(node.children[1])

    def print_eq(self, node: Node):
        print(' ' * self.indent, end='')
        self.print(node.children[0])
        print(' = ', end='')
        self.print(node.children[1])
        print(';')

NODE_MAP = {
    TokenType.ADD: AddNode,
    TokenType.METHOD: MethodNode,
    TokenType.EQ: AssignNode,
    TokenType.PARAMETER: ParameterNode,
    TokenType.STATLIST: StatListNode,
    TokenType.EXPR: ExprlNode,
    TokenType.CALL_FUNC: CallFuncNode,
    TokenType.VAR_DECL: VarDeclNode,
    TokenType.FUNC_DECL: FuncDeclNode,
    TokenType.METHOD_DECL: FuncDeclNode,
    TokenType.BLOCK: BlocklNode,
    TokenType.RETURN_NODE: Node,
}


@dataclasses.dataclass(repr=False)
class Symbol:
    """
    Symbol 里面的符号，一般用来保存一些类型信息之类的
    """
    name: str
    type: str = dataclasses.field(default=None)

    def __repr__(self):
        return f'<{self.name}:{self.type}>' if self.type else self.name


class VariableSymbol(Symbol):
    """变量的 symbol"""


class Type:
    pass


class BuiltInTypeSymbol(Type, Symbol):
    """内置类型"""


class Scope:
    """作用域接口类"""

    def __init__(self, prev: 'BaseScope' = None):
        self.symbols = {}
        self.prev = prev

    def get_scope_name(self):
        return 'global'

    def get_enclosing_scopy(self) -> 'BaseScope':
        return self.prev

    def define(self, symbol: Symbol):
        self.symbols[symbol.name] = symbol

    def resolve(self, name: str) -> Symbol:
        env = self
        while env is not None:
            if name in env.symbols:
                return env.symbols[name]
            env = env.get_enclosing_scopy()
        return None


class MethodSymbol(Scope, Symbol):
    """方法类型
    作为 Scope 是为函数参数存在。
    不过函数参数为什么需要一个特殊的 scope 而不是跟 Local Scope 一起
    """

    def __init__(self, name=None, type=None, prev: 'BaseScope' = None):
        self.name = name
        self.type = type
        super().__init__(prev)


class BaseScope(Scope):
    pass


class GlobalScope(BaseScope):
    def __init__(self, *args, **kwarg):
        super().__init__(*args, **kwarg)
        self.init_type_system()

    def init_type_system(self):
        for type in TYPE_TOKEN:
            self.define(BuiltInTypeSymbol(type))


class LocalScope(BaseScope):
    pass


class Parser:
    def __init__(self, input: Lexer, size: int):
        self.input = input
        self.size = size
        self.p = 0
        self.lookahead: List[Token] = [None] * self.size
        self.ast = None

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

    def node(token_type):
        def decorator(f):
            @functools.wraps(f)
            def wrapper(self, *args, **kwargs):
                node = NODE_MAP[token_type](
                    Token(token_type, token_type, self.LL(1).line),
                    [])
                if self.ast is not None:
                    self.ast.children.append(node)
                else:
                    self.ast = node
                saved = self.ast
                self.ast = node
                result = f(self, *args, **kwargs)
                self.ast = saved
                return result

            return wrapper

        return decorator

    def append_node(token_type):
        def decorator(f):
            @functools.wraps(f)
            def wrapper(self, *args, **kwargs):
                node = Node(
                    Token(token_type, self.LL(1).text, self.LL(1).line),
                    [])
                self.ast.children.append(node)
                return f(self, *args, **kwargs)

            return wrapper

        return decorator

    def program(self):
        self.current_scope = GlobalScope(prev=None)
        self.statlist()

    @node(TokenType.STATLIST)
    def statlist(self):
        while True:
            if self.LL(1).type == TokenType.TYPE:
                if self.LL(3).type == TokenType.LBRACK:
                    self.func_dec()
                else:
                    self.var_dec()
            elif self.LL(1).type == TokenType.LCURLY:
                self.block()
            elif self.LL(1).type == TokenType.ID:
                if self.LL(2).type == TokenType.LBRACK:
                    self.call_func()
                else:
                    self.assign()
            else:
                break

    @node(TokenType.EQ)
    def assign(self):
        self.id()
        self.match(TokenType.EQ)
        self.expr()
        self.match(TokenType.SEMI)

    @node(TokenType.BLOCK)
    def block(self):
        self.match(TokenType.LCURLY)
        self.statlist()
        if self.LL(1).text == 'return':
            self.return_node()
        self.match(TokenType.RCURLY)

    @node(TokenType.RETURN_NODE)
    def return_node(self):
        self.match(TokenType.RETURN)
        self.primary()
        self.match(TokenType.SEMI)

    @node(TokenType.FUNC_DECL)
    def func_dec(self):
        self.type()

        self.id()

        self.match(TokenType.LBRACK)
        self.parameter()
        self.match(TokenType.RBRACK)
        self.block()

    @node(TokenType.PARAMETER)
    def parameter(self):
        while self.LL(1).type == TokenType.TYPE:
            self.type()
            self.id()
            if not self.LL(1).type == TokenType.RBRACK:
                self.match(TokenType.COMMA)

    @node(TokenType.CALL_FUNC)
    def call_func(self):
        self.id()
        self.match(TokenType.LBRACK)
        while self.LL(1).type in {
            TokenType.ID,
            TokenType.NUM,
            TokenType.LBRACK,
        }:
            self.primary()
            if not self.LL(1).type == TokenType.RBRACK:
                self.match(TokenType.COMMA)
        self.match(TokenType.RBRACK)
        self.match(TokenType.SEMI)

    @node(TokenType.VAR_DECL)
    def var_dec(self):
        self.type()
        self.id()
        if self.LL(1).type == TokenType.EQ:
            self.match(TokenType.EQ)
            self.expr()
        self.match(TokenType.SEMI)


    @node(TokenType.EXPR)
    def expr(self):
        if self.LL(2).type != TokenType.ADD:
            self.primary()
        else:
            self.add()

    def add(self):
        node = AddNode(self.LL(2), [])
        saved = self.ast
        self.ast = node

        self.primary()
        while self.LL(1).type == TokenType.ADD:
            add_token = self.LL(1)
            self.match(TokenType.ADD)
            self.primary()

            node = AddNode(add_token, [node])
            self.ast = node
        self.ast = saved
        node = node.children[0] if len(node.children) == 1 else node
        if self.ast is None:
            self.ast = node
        else:
            self.ast.children.append(node)

    def primary(self):
        if self.LL(1).type == TokenType.NUM:
            return self.num()

        if self.LL(1).type == TokenType.ID:
            return self.id()

        if self.LL(1).type == TokenType.LBRACK:
            self.match(TokenType.LBRACK)
            self.expr()
            self.match(TokenType.RBRACK)

    @append_node(TokenType.NUM)
    def num(self):
        self.match(TokenType.NUM)

    @append_node(TokenType.ID)
    def id(self):
        self.match(TokenType.ID)

    @append_node(TokenType.TYPE)
    def type(self):
        self.match(TokenType.TYPE)


class Test(unittest.TestCase):
    def test(self):
        lexer = Lexer(
            """int i = 9;
            float f(int x, float y)
            {
                float i;
                { float z = x+y; i = z; }
                { float z = i+1; i = z; }
                return i;
            }
            void g()
            {
                f(i, 2);
            }
            """)
        token = lexer.next_token()
        while token.type != TokenType.EOF:
            print(token)
            token = lexer.next_token()
        print(token)

    def test_parser(self):
        lexer = Lexer(
            """
            int i=9;
            float f(int x, float y)
            {
                float i;
                { float z = x+y; i = z; }
                { float z = i+1; i = z; }
                return i;
            }
            void g()
            {
                f(i, 2);
            }
            """)
        parser = Parser(lexer, 10)
        parser.program()
        ast = parser.ast
        # prettyprinter.cpprint(ast)
        PrintVistor().print(ast)
