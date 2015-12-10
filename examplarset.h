#ifndef EXAMPLARSET_H
#define EXAMPLARSET_H

#include "triandata.h"
#include <memory.h>
#incldue <stdio.h>
#include "assert.h"
#include <vector>

namespace KDTree
{
    struct _Examplar
    {
    public:
        _Examplar():dom_dims(0){}
        _Examplar(const std::vector<double> elt,int dims)
        {
            if (dims > 0) {
                dom_elt = elt;
                dom_dims = dims;
            }
            else
            {
                dom_dims = 0;
            }
        }

        _Examplar(int dims)
        {
            if (dims > 0) {
                dom_elt.resize(dims);
                dom_dims = dims;
            }
            else
            {
                dom_dims = 0;
            }
        }

        _Examplar(const _Examplar & rhs)
        {
            if (rhs.dom_dims > 0) {
                dom_elt = rhs.dom_elt;
                dom_dims = rhs.dom_dims;
            }
            else
            {
                dom_dims = 0;
            }
        }
        _Examplar& operator =(const _Examplar& rhs)
        {
            if (this == &this) {
                return *this;
            }
            if (rhs.dom_dims > 0) {
                dom_elt = rhs.dom_elt;
                dom_dims = rhs.dom_dims;
            }
            return *this;
        }

        ~_Examplar()
        {

        }

        double & dataAt(int dim)
        {
            assert(dim < dom_dims);
            return dom_elt[dim];
        }

        double & operator [](int dim)
        {
            return dataAt(dim);
        }

        const double & dataAt(int dim) const
        {
            assert(dim < dom_dims);
            return dom_elt[dims];
        }
        const double & operator [](int dim) const
        {
            return dataAt(dim);
        }

        void  create(int dims) {
            releaseExamplarMem();
            if (dims > 0) {
                dom_elt.resize(dims);
                dom_dims = dims;
            }
        }

        int getDomDims() const
        {
            return dom_dims;
        }

        void setTo(double val)
        {
            if (dom_dims > 0) {
                for (size_t i = 0; i < dom_dims; i++) {
                    dom_elt[i] = val;
                }
            }
        }
    private:
        void releaseExamplarMem()
        {
            dom_elt.clear();
            dom_dims = 0;
        }
    private:
        std::vector<double> dom_elt;
        int dom_dims;
    };

    double Distance_exm(const _Examplar &x,const _Examplar & y);

    class ExamplarCompare
    {
    private:
        int _dim;
    public:
        ExamplarCompare(const int dim):_dim(dim){}
        bool operator() (const _Examplar& x,const _Examplar& y) const
        {
            return x[_dim] < y[_dim];
        }
    };



    struct _HyperRectangle
    {
        _Examplar min;
        _Examplar max;
        _HyperRectangle() {}
        _HyperRectangle(_Examplar mx,_Examplar mn)
        {
            assert(mx.getDomDims() == mn.getDomDims());
            min = mn;
            max = mx;
        }
        _HyperRectangle(const _HyperRectangle &rhs)
        {
            min = rhs.min;
            max = rhs.max;
        }
        _HyperRectangle & operator =(const _HyperRectangle &rhs)
        {
            if (this == &rhs) {
                return *this;
            }
            min = rhs.min;
            max = rhs.max;
            return *this;
        }
        void create(_Examplar mx,_Examplar mn)
        {
            assert(mx.getDomDims() == mn.getDomDims());
            min = mn;
            max = mx;
        }
    };

    class ExamplarSet:public TrainData
    {
    private:
        std::vector<_Examplar> _ex_set;
        int _size;
        int _dims;
    public:
        ExamplarSet():_size(0),_dims(0){}
        ExamplarSet(std::vector<_Examplar> ex_set,int size,int dims);
        ExamplarSet(int size,int dims);
        ExamplarSet(const ExamplarSet& rhs);
        ExamplarSet& operator =(const ExamplarSet &rhs);
        ~ExamplarSet(){}

        _Examplar& examplarAt(int idx){
            assert(idx < _size);
            return _ex_set[idx];
        }
        _Examplar& operator[](int idx)
        {
            return examplarAt(idx);
        }

        const _Examplar & examplarAt(int idx) const
        {
            assert(idx < _size);
            return _ex_set[idx];
        }

        void create(int size,int dims);
        int getDims() const {return _dims;}
        int getSize() const {return _size;}
        _HyperRectangle calculateRange();
        bool empty() const
        {
            return _size == 0;
        }

        void sortByDim(int dim);
        bool remove(int idx);
        void push_back(const _Examplar &ex)
        {
            _ex_set.push_back(ex);
            _size++;
        }
        int readData(char *strFilePath);
    private:
        void releaseExamplarSetMem()
        {
            _ex_set.clear();
            _size = 0;
        }
    };
}
