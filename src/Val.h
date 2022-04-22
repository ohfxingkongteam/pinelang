#pragma once
#include "stdc++.h"
using namespace std;
#define INT 0
#define DOU 1
#define STR 2
#define MAP 3
class Val
{
public:
    int INT_VAL;
    double DOU_VAL;
    string STR_VAL;
    map<Val, Val>MAP_VAL;
    int type;
    void del() { INT_VAL = DOU_VAL = 0; STR_VAL.clear(), MAP_VAL.clear(); }
    Val() {}
    Val(int x) { INT_VAL = x; type = INT; }
    Val(double x) { DOU_VAL = x; type = DOU; }
    Val(string x) { STR_VAL = x; type = STR; }
};
ostream& operator << (ostream & out, const Val & v) {
    if (v.type == INT)out << v.INT_VAL;
    if (v.type == DOU)out << v.DOU_VAL;
    if (v.type == STR)out << v.STR_VAL;
    return out;
}
Val operator + (Val a, Val b);
Val operator - (Val a, Val b);
Val operator * (Val a, Val b);
Val operator / (Val a, Val b);

Val operator + (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL + b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL + b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL + b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL + b.DOU_VAL;
    }
    if (a.type == STR && b.type == STR)return a.STR_VAL + b.STR_VAL;
    if (a.type == STR && b.type == INT)return a.STR_VAL + to_string(b.INT_VAL);
    if (a.type == STR && b.type == DOU)return a.STR_VAL + to_string(b.DOU_VAL);
    if (a.type == INT && b.type == STR)return to_string(a.INT_VAL) + b.STR_VAL;
    if (a.type == DOU && b.type == STR)return to_string(a.DOU_VAL) + b.STR_VAL;
	return a;
}

Val operator - (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL - b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL - b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL - b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL - b.DOU_VAL;
    }
	return a;
}

Val operator * (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL * b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL * b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL * b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL * b.DOU_VAL;
    }
	return a;
}

Val operator / (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL / b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL / b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL / b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL / b.DOU_VAL;
    }
	return a;	
}

Val operator % (Val a, Val b) {
    return a.INT_VAL % b.INT_VAL;
}

bool operator == (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL == b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL == b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL == b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL == b.DOU_VAL;
    }
	return false;
}

bool operator  && (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL && b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL && b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL && b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL && b.DOU_VAL;
    }
	return false;
}

bool operator  || (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL || b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL || b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL || b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL || b.DOU_VAL;
    }
	return false;
}

bool operator  < (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL < b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL < b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL < b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL < b.DOU_VAL;
    }
	return false;
}


bool operator  > (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL > b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL > b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL > b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL > b.DOU_VAL;
    }
	return false;
}

bool operator  <= (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL <= b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL <= b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL <= b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL <= b.DOU_VAL;
    }
	return false;
}


bool operator  >= (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL >= b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL >= b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL >= b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL >= b.DOU_VAL;
    }
	return false;
}