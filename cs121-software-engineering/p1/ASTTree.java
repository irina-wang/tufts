interface Expr {}
class IntExpr implements Expr {
    int val;
    IntExpr(int val) {this.val = val;}
}

// class addExpr implements Expr {
//     int val;
//     IntExpr(int val) {this.val = val;}
// }


class AddExpr implements Expr {
    Expr left, right;
    AddExpr(Expr left, Expr right) {    
        this.left = left;
        this.right = right;
    }
}


class MultiExpr implements Expr {
    Expr left, right;
    MultiExpr(Expr left, Expr right) {    
        this.left = left;
        this.right = right;
    }
}


Expr e345 = new MultiExpr (new AddExpr(new IntExpr(3), new IntExpr(4), new IntExpr(5)));

int eval(Expr e){
    if (e instanceof IntExpr){
        IntExpr ie = (IntExpr) e;
        return ie.val;
    }
    // if (e instanceof MultiExpr){
    //     MultiExpr ie = (MultiExpr) e;
    //     return ie.val * ;
    // }
    // if (e instanceof AddExpr){
    //     AddExpr ie = (AddExpr) e;
    //     return ie.val;
    // }

}


// oo style traversal 

// add int eval()


int eval() { return left.eval() + right.eval(); }
void pretty_print(Expr e) {
    void pretty_print() {};
}

/* visit pattern goals: 
    Use the OO-style traversal 
    Implement the traversal code once
*/ 


interface Expr {}
class IntExpr implements Expr {}
class AddExpr implements Expr {}
class MultiExpr implements Expr {}

interface Visitor{}
class Eval implements Visitor {
    void visitIntExpr(IntExpr e) {...};;
    void visitAddExpr(AddExpr e) {...};;
    void visitMultiExpr(AddExpr e) {...};
}

class PrettyPrint implements Vistor {...}

Expr ex = new MultExpr (...);
Visitor ev = new Eval();

ex.some_method(ev);
ev.some_method(ex);

// Problem only have single dispatch 

interface I {}
class A implements I { void acceept(Z z) {z.visitA(this);}}
class B implements I { void acceept(Z z) {z.visitB(this);}}

interface Z {}
class X implements Z {
    void vistA(I i) { System.out.println("z is X, i is A");}
    void vistB(I i) { System.out.println("z is X, i is A");}
}
class Y implements Z {
    void vistA(I i) { System.out.println("z is Y, i is A");}
    void vistB(I i) { System.out.println("z is Y, i is A");}
}


//___________________________

interface Expr {
    void accept(Void v);
    int res;
}
class IntExpr implements Expr {
    void accept(Visitor v){
        v.visitIntExpr(this);
        // v.visit(this);
    }
}
class AddExpr implements Expr {
    void accept(Visitor v){
        left.accept(v);
        right.accept(v);
        v.visitAddExpr(this);
         // v.visit(this);
    }
}
class MultExpr implements Expr {
    void accept(Visitor v){
        left.accept(v);
        right.accept(v);
        v.visitMultExpr(this);
         // v.visit(this);
    }
}


/////////////////////////////////////////////////////////

interface Vistor{ ... }
class Eval implements Vistor {
    void visitIntExpr(IntExpr e){
        e.res = e.eval;
    }

    void visitAddExpr(AddExpr e){
        e.res = e.left.res + e.left.res;
    
    }
    void visitAddExpr(AddExpr e){
        e.res = e.left.res * e.left.res;
    }

}


Expr i = new AddExpr(new IntExpr(3), new IntExpr(4));
Visitor v = new Eval();




