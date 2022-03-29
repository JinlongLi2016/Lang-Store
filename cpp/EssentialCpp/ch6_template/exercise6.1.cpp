
template<typename elemType>
class example{
    public:
        example(elemType& min, elemType& max);
        example(const elemType *array, int size);
        elemType& operator[](int index);

        bool operator==(const example1&) const;
        bool insert(const elemType*, int);
        bool insert(elemType&);

        elemType min() const { return _min; }
        elemType max() const { return _max; }

        void min(elemType&);
        void max(elemType&);

        int count(elemType& value) const;
    
    private:
        int size;
        elemType *parray;
        elemType _min;
        elemType _max;
};

// 形式参数，与类型相关用引用的形式
// 返回类型，与类型相关无须用引用的形式（采用传值的方式）

