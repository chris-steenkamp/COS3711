#include "album.h"
#include <QString>

Album::Album(QString composer, QString name, float repValue, int rating) :
    m_Composer(composer),
    m_Name(name),
    m_ReplacementValue(repValue),
    m_Rating(rating)
{

}

QString Album::name() const
{
    return m_Name;
}

QString Album::composer() const
{
    return m_Composer;
}

float Album::replacementValue() const
{
    return m_ReplacementValue;
}

int Album::rating() const
{
    return m_Rating;
}

QString Album::toString() const
{
    return QString("%0, %1 R%2, %3/100")
            .arg(name())
            .arg(composer())
            .arg(QString::number(static_cast<double>(replacementValue()), 'f', 2)
                 .arg(rating()));
}

void Album::setName(QString name)
{
    m_Name = name;
}

void Album::setComposer(QString composer)
{
    m_Composer = composer;
}

void Album::setReplacementValue(float value)
{
    m_ReplacementValue = value;
}

void Album::setRating(int rating)
{
    m_Rating = rating;
}


