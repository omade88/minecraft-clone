class Block {
public:
    Block();
    ~Block();

    int getType() const;
    void setType(int type);

private:
    int type;
};