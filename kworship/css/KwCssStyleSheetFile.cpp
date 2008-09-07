/**
 * @file KwCssStyleSheetFile.cpp
 * @brief File backed cascading style sheet.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwCssStyleSheetFile.h"

/*
 * Constructors + destructors
 */

/// Default constructor.
KwCssStyleSheetFile::KwCssStyleSheetFile(QString path)
: KwCssStyleSheet()
, m_path(path)
{
}

/// Destructor.
KwCssStyleSheetFile::~KwCssStyleSheetFile()
{
}

/*
 * Main interface.
 */

/// Load the file.
void KwCssStyleSheetFile::load()
{
  /// @todo Implement
}

/// Save the file.
void KwCssStyleSheetFile::save() const
{
  /// @todo Implement
}

