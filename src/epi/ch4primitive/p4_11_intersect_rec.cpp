#include <iostream>

using namespace std;

struct Line {
    int loc;
    int len;
};

struct Rect {
    Line w;
    Line h; 
 };

void dump_rect(Rect &r) {
    cout <<   "x: " << r.w.loc << ", y: " << r.h.loc 
         << ", w: " << r.w.len << ", h: " << r.h.len << endl;
}

// len 0 is also instersection
Line get_intersect_line(Line &l1, Line &l2) {
    Line i;
    if (l1.loc < l2.loc) {
        i.loc = l2.loc;
        i.len = l1.loc + l1.len - l2.loc;
    } else { // l1 >= l2 
        i.loc = l1.loc;
        i.len = l2.loc + l2.len - l1.loc;
    }
    return i;
}

Rect get_intersect_rect(Rect &r1, Rect &r2) {
    Rect i;
    i.w = get_intersect_line(r1.w, r2.w);
    i.h = get_intersect_line(r1.h, r2.h);

    return i;
}

bool is_intersected(Rect & i) {
    if (i.h.len >= 0 && i.w.len >= 0) {
        cout << " intersect !!" << endl; 
        return true;
    } else {
        cout << " not intersect !!" << endl;
        return false;
    }
}


void test_p4_11_intersect_rec() {
    cout << " * " << __func__ << endl;

    Rect r1;
        r1.w.loc = 1; r1.w.len = 5;
        r1.h.loc = 2; r1.h.len = 4;
    Rect r2;
        r2.w.loc = 5; r2.w.len = 2;
        r2.h.loc = 3; r2.h.len = 4;
    Rect i = get_intersect_rect(r1, r2);
    dump_rect(i);
    is_intersected(i);
        // if both x axis, and y axis are intersect. 
        //   Rectanges are intersected !!!

        r1.w.loc = 1; r1.w.len = 3;
        r1.h.loc = 2; r1.h.len = 4;
        r2.w.loc = 5; r2.w.len = 2;
        r2.h.loc = 3; r2.h.len = 4;
    i = get_intersect_rect(r1, r2);
    dump_rect(i);
    is_intersected(i);


}