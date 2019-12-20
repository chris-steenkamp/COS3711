#ifndef ALBUM_H
#define ALBUM_H

#include <QString>

class Album
{
public:
    Album(QString composer, QString name, float repValue, int rating);

    QString composer() const;
    QString name() const;
    float replacementValue() const;
    int rating() const;
    QString toString() const;

    void setComposer(QString);
    void setName(QString);
    void setReplacementValue(float);
    void setRating(int);
private:
    QString m_Composer;
    QString m_Name;
    float m_ReplacementValue;
    int m_Rating;
};

#endif // ALBUM_H
