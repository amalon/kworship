#ifndef _KwCssStandardise_h_
#define _KwCssStandardise_h_

/**
 * @file KwCssStandardise.h
 * @brief Macros for css standardisation.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssScope.h"

/// Simple class for accessing a style.
template <typename T>
class KwCssStyleAccessor
{
  public:
    virtual ~KwCssStyleAccessor()
    {
    }
    /*
     * Main interface
     */
    T operator () (const KwCssScope* scope) const
    {
      return scope->getStyles().getStyle<T>(getName());
    }
  protected:
    virtual QString getName() const = 0;
};

/// Start the root css namespace.
#define KWCSS_ROOT_NAMESPACE(NAME) \
  namespace NAME \
  { \
    QString _scopeName() \
    { \
      return #NAME; \
    }

/// Start a non-root css namespace.
#define KWCSS_START_NAMESPACE(PREV,NAME) \
  namespace NAME \
  { \
    QString _scopeName() \
    { \
      return #PREV "." #NAME; \
    }

/// End a css namespace.
#define KWCSS_END_NAMESPACE() \
  };

/// Define a property in a css namespace.
#define KWCSS_DEFINE_PROPERTY(TYPE, LNAME) \
  class Acc_##LNAME : public KwCssStyleAccessor< TYPE > \
  { \
    protected: \
      virtual QString getName() const \
      { \
        QString name = _scopeName(); \
        name.append("." #LNAME); \
        return name; \
      } \
  } LNAME;

#endif // _KwCssStandardise_h_

