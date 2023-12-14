#ifndef MESSAGESTRUCTS_H
#define MESSAGESTRUCTS_H

#include <QDataStream>

qint16 const kMessage1Header = 0xABCD;
qint16 const kMessage2Header = 0x1234;

;
#pragma pack(push, 1)
struct Message1
{
    Message1()
    {
        this->height = 0;
    }

    Message1(qint16 height){
        this->height = height;
    }

    quint16 header = kMessage1Header;
    quint16 height;


    friend QDataStream& operator<<(QDataStream &stream, const Message1 &mes){
        stream << mes.header;
        stream << mes.height;
        return stream;
    }

    friend QDataStream& operator >>(QDataStream &stream, Message1 &mes){
        stream >> mes.header;
        stream >> mes.height;
        return stream;
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Message2
{
    quint16 header = kMessage2Header;

    friend QDataStream& operator<<(QDataStream &stream, const Message2 &mes){
        stream << mes.header;
        return stream;
    }

    friend QDataStream& operator >>(QDataStream &stream, Message2 &mes){
        stream >> mes.header;
        return stream;
    }
};
#pragma pack(pop)

#endif // MESSAGESTRUCTS_H
