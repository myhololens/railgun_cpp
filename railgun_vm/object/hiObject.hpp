#ifndef _HI_OBJECT_HPP
#define _HI_OBJECT_HPP

#include "klass/klass.hpp"
#include <assert.h>

class HiString;

class ObjectKlass : public Klass {
private:
    ObjectKlass();
    static ObjectKlass* instance;

public:
    static ObjectKlass* get_instance();
};

class HiObject {
private:
    long _mark_word;
    Klass* _klass;
    Map<HiObject*, HiObject*>* _obj_dict;

public:
    HiObject() {
        _mark_word = 0;
        _klass = ObjectKlass::get_instance();
        _obj_dict = new Map<HiObject*, HiObject*>();
    }

    Klass* klass()             { assert(_klass != NULL); return _klass; }
    void set_klass(Klass* x)   { _klass = x; }

    Map<HiObject*, HiObject*>* obj_dict()           { return _obj_dict; }
    Map<HiObject*, HiObject*>** obj_dict_address()  { return &_obj_dict; }

    void print();
    HiObject* greater  (HiObject* x);
    HiObject* less     (HiObject* x);
    HiObject* equal    (HiObject* x);
    HiObject* not_equal(HiObject* x);
    HiObject* ge       (HiObject* x);
    HiObject* le       (HiObject* x);

    HiObject* add(HiObject* x);
    HiObject* sub(HiObject* x);
    HiObject* mul(HiObject* x);
    HiObject* div(HiObject* x);
    HiObject* mod(HiObject* x);

    HiObject* getattr(HiObject* x);
    HiObject* setattr(HiObject* x, HiObject* y);
    HiObject* subscr(HiObject* x);

    // interfaces for GC.
    void oops_do(OopClosure* closure);
    size_t size();
    char* new_address();
    void set_new_address(char* addr);
};

/*
 * meta-klass for the object system.
 */

class TypeKlass : public Klass {
private:
    TypeKlass() {}
    static TypeKlass* instance;

public:
    static TypeKlass* get_instance();

    virtual void print(HiObject* obj);
};

class HiTypeObject : public HiObject {
private:
    Klass*  _own_klass;

public:
    HiTypeObject();

    void    set_own_klass(Klass* k);
    Klass*  own_klass()             { return _own_klass; }

    void* operator new(size_t size);
};

#endif
