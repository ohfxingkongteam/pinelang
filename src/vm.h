#pragma once
#include "eval.h"
namespace vm {
    vector<string> lines;
    void clear(string &s) {
        //处理头尾空格
        while (s.size() && s.back() == ' ')s.pop_back();
        reverse(s.begin(), s.end());
        while (s.size() && s.back() == ' ')s.pop_back();
        reverse(s.begin(), s.end());
    }
    int cur = 0;
    map<int, int>jmp;
    void parser_while(string s);
    void parser_if(string s);
    void parser_print(string s);
    void parser_scanf(string s);
    void parser_end(string s);// 处理 '}'
    void cal_jmp();
    void parser(string s) {
        if (s.find("while") != s.npos) parser_while(s);
        else if (s.find("if") != s.npos) parser_if(s);
        else if (s.find("scanf") != s.npos) parser_scanf(s);
        else if (s.find("print") != s.npos)parser_print(s);
        else if (count(s.begin(), s.end(), '}'))parser_end(s);
        else {
            eval::Expression(s);
            cur++;
        }
    }
    void run(string s) {
        stringstream ss; ss << s;
        string str;
        while (getline(ss, str)) {
            clear(str);
            if (str.length() > 0)lines.push_back(str);
        }
        cal_jmp();//处理跳转
        cur = 0;
        while (cur < lines.size()) {
            //cout << "lines : " << cur << endl;
            parser(lines[cur]);
        }
    }
    void cal_jmp() {
        stack<pair<string, int>>stk;
        for (int i = 0; i < lines.size(); i++) {
            if (count(lines[i].begin(), lines[i].end(), '{')) {
                if (lines[i].find("while") != lines[i].npos) {
                    stk.push({ "while",i });
                }
                else {
                    stk.push({ "if",i });
                }
            }
            if (count(lines[i].begin(), lines[i].end(), '}')) {
                if (stk.top().first == "if") {
                    jmp[stk.top().second] = i + 1;
                    jmp[i] = i + 1;
                }
                else {
                    jmp[stk.top().second] = i + 1;
                    jmp[i] = stk.top().second;
                }
                stk.pop();
            }
        }
    }
    void parser_print(string s) {
        cout << eval::Expression(s.substr(5, s.length() - 5)) << endl;
        cur++;
    }
    void parser_scanf(string s) {
        string eq; cin >> eq;
        eval::Expression(s.substr(5, s.length() - 5) + " = " + eq);
        cur++;
    }
    void parser_while(string s) {
        s.pop_back();
        Val x = eval::Expression(s.substr(5, s.length() - 5));
        if (x == 1)cur++;
        else cur = jmp[cur];
    }
    void parser_if(string s) {
        s.pop_back();
        Val x = eval::Expression(s.substr(2, s.length() - 2));
        if (x == 1)cur++;
        else cur = jmp[cur];
    }
    void parser_end(string s) {
        cur = jmp[cur];
    }
}







