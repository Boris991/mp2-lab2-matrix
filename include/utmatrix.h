// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
    ValType* pVector;
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // конструктор копирования
    ~TVector();
    int GetSize() { return Size; } // размер вектора
    int GetStartIndex() { return StartIndex; } // индекс первого элемента
    ValType& operator[](int pos);             // доступ
    bool operator==(const TVector& v) const;  // сравнение
    bool operator!=(const TVector& v) const;  // сравнение
    TVector& operator=(const TVector& v);     // присваивание
    
    // скалярные операции
    TVector  operator+(const ValType& val);   // прибавить скаляр
    TVector  operator-(const ValType& val);   // вычесть скаляр
    TVector  operator*(const ValType& val);   // умножить на скаляр
    
    // векторные операции
    TVector  operator+(const TVector& v);     // сложение
    TVector  operator-(const TVector& v);     // вычитание
    ValType  operator*(const TVector& v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {   
      for (int i = 0; i < v.GetSize; i++)
      {
          in >> v.pVector[i];
      }
      return in;
  }
  friend ostream& operator<<(ostream &out, TVector &v)
  {
      for (int i = 0; i < v.GetSize; i++)
      {
          out <<  v.pVector[i] << ' ';
      }
      return out;
  }

  
};
/*template<class ValType>
istream& operator>>(istream& in, TVector<ValType>& v)
{
    for (int i = 0; i < v.GetSize() - v.GetStartIndex(); i++)
        in >> v.pVector[i];
    return in;
}
template <class ValType>
ostream& operator<<(ostream& out, const TVector<ValType> v)
{

    for (int i = 0; i < v.GetSize() - v.StartIndex(); i++)
        out << v.pVector[i] << ' ';
    return out;
}
*/
template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 0 || si < 0 || (s > MAX_VECTOR_SIZE) || (si >= MAX_VECTOR_SIZE))
    {
        throw "unable to create vector with uncorrect parametrs";
    }
    Size = s;
    StartIndex = si;
    pVector = new ValType[s];//1
    //Valtype tmp=Valtype(0);
    for (int i = 0; i < s; i++)//2
    {
        this->pVector[i] = 0;//(0);
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    this->pVector = new ValType[Size];
    for (int i = 0; i < Size; i++)//3
    {
        this->pVector[i] = v.pVector[i];
    }
} 

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[]pVector;
    pVector = nullptr;
    Size = 0;
    StartIndex = 0;
} 

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    ValType tmp(0);
    if (pos < 0 || pos >= Size + StartIndex)
    {
        throw "unable to create vector with uncorrect parametrs";
    }
    else
        if (pos < StartIndex)
        {
            return tmp;
        }
        else
        {
            return pVector[pos - StartIndex];
        }
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
    if (this != &v)
    {
        if (Size != v.Size || StartIndex != v.StartIndex)
        {
            return false;
        }
        for (int i = 0; i < Size; i++)
        {
            if (pVector[i] != v.pVector[i])
            {
                return false;
            }
        }     
    }
    return true;
}

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
    return !(*this == v);
}
   

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector<ValType>& v)
{
    if (Size != 0)
    {
        delete[]pVector;
    }
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i <v.Size; i++)//
    {
        pVector[i] = v.pVector[i];
    }
    return *this;
} 

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
    TVector<ValType>temp(*this);
    for (int i = 0; i < Size; i++)
    {
        temp.pVector[i] += val;
    }
    return temp;
}

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
    TVector<ValType>temp(*this);
    for (int i = 0; i < Size; i++)
    {
        temp.pVector[i] -= val;
    }
    return temp;
}

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
    TVector<ValType>temp(*this);
    for (int i = 0; i < Size; i++)
    {
        temp.pVector[i] = this->pVector[i] * val;
    }
    return temp;
}

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
    if ((Size != v.Size) || (StartIndex != v.StartIndex)) throw "uncorrect size vector";
    TVector<ValType>temp(*this);
    for (int i = 0; i < Size;i++)
    {
        temp.pVector[i] =temp.pVector[i]+v.pVector[i];
    }
    return temp;
}

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
    TVector<ValType>temp(*this);
    if ((Size != v.Size) || (StartIndex != v.StartIndex)) throw "uncorrect size vector";
    for (int i = 0; i < this->Size; i++)
    {
        temp.pVector[i] = temp.pVector[i] - v.pVector[i];
    }
    return temp;
}

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
    if (Size != v.Size)throw "uncorrect size vector";
    ValType ScalProduct(0);
    TVector<ValType>temp(*this);
    for (int i = 0; i < this->Size; i++)
    {
        ScalProduct =ScalProduct+ temp.pVector[i] * v.pVector[i];
    }
    return ScalProduct;
}


/*template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
    if (Size != v.Size)
    {
        throw "uncorrect size vector";
    }
    ValType ScalProduct(0);
    TVector<ValType>temp(*this);
    for (int i = 0; i < this->Size; i++)
    {
        ScalProduct += temp.pVector[i] * v.pVector[i];
    }
    return ScalProduct;
} 

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s<0 || si<0 || (s>MAX_VECTOR_SIZE)|| (si>=MAX_VECTOR_SIZE))
    {
        throw "unable to create vector with uncorrect parametrs";
    }
    Size = s;
    StartIndex = si;
    pVector = new ValType[s-si];
    for (int i = 0; i < s-si; i++)
    {
        this->pVector[i] = 0;
    }
} 

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    this->pVector = new ValType[Size- StartIndex];
    for (int i = 0; i < Size- StartIndex; i++)
    {
        this->pVector[i] = v.pVector[i];
    }
}

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[]pVector;
    pVector = nullptr;
    Size = 0;
    StartIndex = 0;
} 

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    ValType tmp(0);
    if (pos < 0 || pos >= Size)
    {
       throw "unable to create vector with uncorrect parametrs";
    }
    else
        if (pos<StartIndex)
        {
            return tmp;
        }
        else
        {
            return pVector[pos];
        }    
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if (this != &v)
    {
        if (this->Size == v.Size || this->StartIndex == v.StartIndex)
        {
            for (int i = 0; i < Size - StartIndex; i++)
            {
                if (pVector[i] != v.pVector[i])
                {
                    return 0;
                }
            }
            return 1;
        }
        else return 0;
    }
    else return 1;
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    if (this != &v)
    {
        if (this->Size == v.Size || this->StartIndex == v.StartIndex)
        {
            for (int i = 0; i < Size; i++)
            {
                if (pVector[i] == v.pVector[i])
                {
                    return 1;
                }
            }
            return 0;
        }
        else return 1;
    } 
    else return 0;
} 

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector<ValType> &v)
{
    if (Size != 0)
    {
        delete[]pVector;
    }
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size-StartIndex];
    for (int i = 0; i < Size-StartIndex; i++)
    {
        pVector[i] = v.pVector[i];
    }
    return *this;
} 

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
    TVector<ValType>temp(*this);
    for (int i = 0; i < Size - StartIndex; i++)
    {
        temp.pVector[i] += val;
    }
    return temp;
} 

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
    TVector<ValType>temp(*this);
    for (int i = 0; i < Size - StartIndex; i++)
    {
        temp.pVector[i] -= val;
    }
    return temp;
} 

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
    TVector<ValType>temp(*this);
    for (int i = 0; i < Size - StartIndex; i++)
    {
        temp.pVector[i] = this->pVector[i] * val;
    }
    return temp;
} 

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
    if ((Size != v.Size) || (StartIndex != v.StartIndex)) throw "uncorrect size vector";
    TVector<ValType>temp(*this);
    for (int i = 0; i < Size - StartIndex; i++)
    {
        temp.pVector[i] += v.pVector[i];
    }
    return temp;
} 

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
    TVector<ValType>temp(*this);
    if ((Size != v.Size) || (StartIndex != v.StartIndex)) throw "uncorrect size vector";
    for (int i = 0; i < this->Size; i++)
    {
        temp.pVector[i] -= v.pVector[i];
    }
    return temp;
} 

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
    if (Size != v.Size)throw "uncorrect size vector";
    ValType ScalProduct(0);
    TVector<ValType>temp(*this);
    for (int i = 0; i < this->Size; i++)
    {
        ScalProduct += temp.pVector[i] * v.pVector[i];
    }
    return ScalProduct;
} 

*/


// Верхнетреугольная матрица
template <class T>
class TMatrix 
{
private:
    TVector<TVector<T>> P;
    int Size;
public:
    //int GetSize() { return Size; }
    TMatrix(int s = 10)
    {
        if (s > MAX_MATRIX_SIZE || s < 0)
        {
            throw "uncorrect size matrix";
        }
        P = TVector<TVector<T>>(s);
        Size = s;
        for (int i = 0; i < Size; i++)
        {
            P[i] = TVector<T>(Size - i, i);
        }
    };
   TMatrix(const TMatrix& tmp)
    {
        P = TVector<TVector<T>>(tmp.P);
        Size = tmp.Size;
    };
    ~TMatrix() {};
    
    TMatrix& operator=(const TMatrix& tmp)
    {
        P = tmp.P;
        Size = tmp.Size;
        return *this;
    };
    TVector<T>& operator[](int k)
    {
        return P[k];
    };
    
    TMatrix operator*(TMatrix tmp)
    {
        TMatrix res(this->Size);
        if (Size != tmp.Size)
        {
            throw "uncorrect size of matrix";
        }
            for (int i = 0; i < Size; i++)
            {
                for (int j = i; j < Size; j++)
                {
                    int q = 0;
                    for (int k = i; k <= j; k++)
                    {
                        q += (*this)[i][k] * tmp[k][j];
                    }
                    res[i][j] = q;
                }
            }
        return res;
    }
    TMatrix operator+(TMatrix tmp)
    {
        TMatrix res(*this);
        if (Size != tmp.Size)
        {
            throw "uncorrect size of matrix";
        }
            res.P = res.P + tmp.P;
        
        return res;
    }
    TMatrix operator-(TMatrix tmp)
    {
        TMatrix res(*this);
        if (Size != tmp.Size)
        {
            throw "uncorrect size of matrix";
        }
            res.P = res.P - tmp.P;


        return res;
    }
    bool operator==(const TMatrix& mt) const
    {
        if (this != &mt)
        {
            if (this->P == mt.P)
            {
                return 1;
            }
            else return 0;
        }
        return 1;
    }
    bool operator!=(const TMatrix& mt) const
    {
        if (this != &mt)
        {
            if (this->P == mt.P)
            {
                return 1;
            }
            else return 0;
        }
        return 1;
    }
    // ввод / вывод
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.P[i];
        return in;
    }
    /*friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
        {
            //out << P[i] << endl;
            /*for (int i = 0; i < mt.Size; i++)
            {
                out << mt[i][j]<<' ';
            }
            out << endl;
            
        }
        return out;
    }
    */
};

#endif
