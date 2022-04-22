#pragma once
#include"Val.h"
namespace eval {
#define OP 0
#define CON 1
#define VAR 2
    class Reader {
        stringstream ss;
    public:
        Reader() {}
        Reader(string s) { ss << s; }
        char get() { return ss.peek(); }//��õ�ǰλ�õ��ַ�
        void next() { ss.get(); }//�±��һ
        bool has_next() { return ss.peek() != -1; }//�Ƿ�����һ��
        void clear() { ss.clear(); }//���
    };

    set<char>operator_set = { '+','-','*','/','(',')','=','^' ,'<','>','?',',','!',';','%','&','|' };

    class Token {
    public:
        Val con;//����
        char op;//������
        string var;//������
        int type;
        Token(char ch) { type = OP; op = ch; }
        Token(Val x) { type = CON; con = x; }
        Token(string s) { type = VAR; var = s; }
    };
    ostream& operator << (ostream & out, const Token & v) {
        if (v.type == OP)out << v.op;
        if (v.type == CON)out << v.con;
        if (v.type == VAR)out << v.var;
        return out;
    }
    Reader rd;
    Token parser_op();
    Token parser_num();
    Token parser_str();
    Token parser_var();
    vector<Token> Lexer(string s) {
        rd.clear();
        rd = Reader(s);
        vector<Token>v;//����ֵ
        while (rd.has_next()) {
            //����ǿո�tab �� �س� �� ����
            while (rd.has_next() && rd.get() == ' ' || rd.get() == '\t' || rd.get() == '\n')rd.next();
            //����Ǹ����ŵĻ�
            if (operator_set.count(rd.get())) {
                v.push_back(parser_op());
            }
            //����Ǹ������Ļ�
            else if (isalpha(rd.get()) || rd.get() == '_') {
                v.push_back(parser_var());
            }
            //�����ǣ���Ӧ���Ǹ�������
            else {
                if (rd.get() == '"')v.push_back(parser_str());
                else v.push_back(parser_num());
            }
        }
        return v;
    }


    /*
        == a
        -> b
        <= c
        >= d
    */
    Token parser_op() {
        char op = rd.get(); rd.next();
        if (op == '=') {
            if (rd.get() == '=') {
                rd.next();
                return Token('a');
            }
            else return Token(op);
        }
        else if (op == '-') {

            if (rd.get() == '>') {
                rd.next();
                return Token('b');
            }
            else return Token(op);
        }
        else if (op == '<') {
            if (rd.get() == '=') {
                rd.next();
                return Token('c');
            }
            else return Token(op);
        }
        else if (op == '>') {
            if (rd.get() == '=') {
                rd.next();
                return Token('d');
            }
            else return Token(op);
        }
        return Token(op);
    }
    Token parser_num() {
        //ͨ���Ƿ���� 'e' '.' ���ж��Ƿ��Ǹ�������
        string s; s.push_back(rd.get()); rd.next();
        while (isdigit(rd.get()) || rd.get() == '.' || rd.get() == 'e') {
            s.push_back(rd.get()), rd.next();
        }
        if (count(s.begin(), s.end(), '.') || count(s.begin(), s.end(), 'e')) {
            return Val(stof(s));
        }
        else {
            return Val(stoi(s));
        }
    }

    Token parser_var() {
        string s;
        while (isalpha(rd.get()) || isdigit(rd.get()) || rd.get() == '_') {
            s.push_back(rd.get());
            rd.next();
        }
        return Token(s);
    }


    Token parser_str() {
        rd.next();
        string s;
        while (rd.get() != '"') {
            s.push_back(rd.get());
            rd.next();
        }
        rd.next();
        return Token(Val(s));
    }

    map<string, Val>var_mp;

    class TreeNode {
    public:
        Val x;
        char op;
        string var;
        int type;
        TreeNode *L;
        TreeNode *R;
        TreeNode() {};
        TreeNode(TreeNode *_L, char _op, TreeNode *_R) {
            type = OP;
            op = _op;
            L = _L, R = _R;
        }
        TreeNode(Val _x) {
            type = CON;
            x = _x;
        }
        TreeNode(string _var) {
            var = _var;
            type = VAR;
        }
        Val eval() {
            if (type == CON)return x;
            else if (type == VAR)return var_mp[var];
            switch (op)
            {
            case '+':return L->eval() + R->eval();
            case '-':return L->eval() - R->eval();
            case '*':return L->eval() * R->eval();
            case '/':return L->eval() / R->eval();
            case '<':return L->eval() < R->eval();
            case '>':return L->eval() > R->eval();
            case 'c':return L->eval() <= R->eval();
            case 'd':return L->eval() >= R->eval();
            case '%':return L->eval() % R->eval();
            case '=':
                var_mp[L->var] = R->eval();
                return R->eval();
            case 'a':return L->eval() == R->eval();
            case 'b':
                if (L->eval() == 1 && R->eval() == 0)return 0;
                else return 1;
            case '|':return L->eval() || R->eval();
            case '&':return L->eval() && R->eval();
            case '!':return !(R->eval() == 1);
            }
			return nullptr;
        }
    };

    stack<TreeNode*>num_stk;
    stack<char>op_stk;
    void addnode() {
        TreeNode *R = num_stk.top(); num_stk.pop();
        TreeNode *L = new TreeNode(Val(0));
        char op = op_stk.top(); op_stk.pop();
        if (op == '!') {
            num_stk.push(new TreeNode(L, op, R));
        }
        else {
            if (num_stk.size())L = num_stk.top(), num_stk.pop();
            num_stk.push(new TreeNode(L, op, R));
        }
    }

    void clear(string &s) {
        while (s.size() && s.back() == ' ')s.pop_back();
        reverse(s.begin(), s.end());
        while (s.size() && s.back() == ' ')s.pop_back();
        reverse(s.begin(), s.end());
    }
    int level[128];//���ȼ�
    Val Expression(string s) {
        clear(s);
        level['!'] = 5;
        level['*'] = level['/'] = 2;
        level['+'] = level['-'] = 1;
        level['='] = -5;
        level['a'] = level['b'] = -4;
        level['|'] = -3, level['&'] = -2;
        level['('] = level[')'] = -100;
        while (num_stk.size())num_stk.pop();
        while (op_stk.size())op_stk.pop();
        for (auto t : Lexer(s)) {
            if (t.type == CON) {
                num_stk.push(new TreeNode(t.con));
            }
            else if (t.type == VAR) {
                num_stk.push(new TreeNode(t.var));
            }
            else {
                switch (t.op)
                {
                case '(':
                    op_stk.push('(');
                    break;
                case ')':
                    while (op_stk.size() && op_stk.top() != '(')addnode();
                    op_stk.pop();
                    break;
                default:
                    while (op_stk.size() && level[op_stk.top()] >= level[t.op])addnode();
                    op_stk.push(t.op);
                }
            }
        }
        while (op_stk.size())addnode();
        return num_stk.top()->eval();
    }
}












