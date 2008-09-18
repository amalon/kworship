#ifndef _KwSongdbFilter_h_
#define _KwSongdbFilter_h_

/**
 * @file KwSongdbFilter.h
 * @brief Filtering structures.
 * @author James Hogan <james@albanarts.com>
 */

#include <QString>
#include <QStringList>

/// A level in the filter stack.
struct KwSongdbFilterLevel
{
  QString tableName;
  QString idExpression;
  QString labelExpression;
  QStringList innerJoinClauses;
  QStringList whereClauses;
  QStringList orderBy;
};

/// A stack of filters.
typedef QVector<KwSongdbFilterLevel> KwSongdbFilterLevelList;

#endif // _KwSongdbFilter_h_
