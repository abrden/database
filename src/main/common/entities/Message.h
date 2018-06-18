#ifndef DATABASE_MESSAGE_H
#define DATABASE_MESSAGE_H


class Message {

    private:
        const long mtype;
    public:
        Message(long mtype);
        long get_mtype() const;
};


#endif //DATABASE_MESSAGE_H
