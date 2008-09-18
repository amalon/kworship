/**
 * @file KwSongdbTree.h
 * @brief A tree widget with songs from songdb.
 * @author James Hogan <james@albanarts.com>
 */

#include "KwSongdbTree.h"
#include "KwSongdbTreeGroupAction.h"
#include "KwSongdbModel.h"
#include "KwSongdbFilterNode.h"

#include <QActionGroup>

/*
 * Constructors + destructor.
 */

/// Primary constructor.
KwSongdbTree::KwSongdbTree(QWidget* parent)
: QTreeView(parent)
, m_model(new KwSongdbModel(this))
, m_groupByActions(new QActionGroup(this))
{
  KwSongdbFilterLevelList* filters;

  filters = new KwSongdbFilterLevelList;
  filters->resize(2);
  (*filters)[0].tableName = "Song";
  (*filters)[0].idExpression = "Song.id";
  (*filters)[0].labelExpression = "Song.name";
  (*filters)[0].orderBy << "Song.name ASC";
  (*filters)[1].tableName = "SongVersion";
  (*filters)[1].idExpression = "SongVersion.id";
  (*filters)[1].labelExpression = "SongVersion.name";
  (*filters)[1].innerJoinClauses << "SongVersion ON SongVersion.song_id = Song.id";
  (*filters)[1].orderBy << "SongVersion.name ASC";
  KwSongdbTreeGroupAction* actionNameVersion = new KwSongdbTreeGroupAction("Song name / Version", filters, m_groupByActions);
  connect(actionNameVersion, SIGNAL(triggered(const KwSongdbFilterLevelList*)), this, SLOT(groupBy(const KwSongdbFilterLevelList*)));

  filters = new KwSongdbFilterLevelList;
  filters->resize(2);
  (*filters)[0].tableName = "SongBook";
  (*filters)[0].idExpression = "SongBook.id";
  (*filters)[0].labelExpression = "CONCAT(SongBook.abreviation, \" \", SongBook.name)";
  (*filters)[0].orderBy << "SongBook.name ASC";
  (*filters)[1].tableName = "SongVersion";
  (*filters)[1].idExpression = "SongVersion.id";
  (*filters)[1].labelExpression = "CONCAT(SongBookSong.book_number, \" - \", Song.name)";
  (*filters)[1].innerJoinClauses << "SongBookSong ON SongBookSong.book_id = SongBook.id"
                                 << "SongVersion ON SongVersion.id = SongBookSong.version_id"
                                 << "Song ON Song.id = SongVersion.song_id";
  (*filters)[1].orderBy << "SongBookSong.book_number ASC";
  KwSongdbTreeGroupAction* actionBookNumber = new KwSongdbTreeGroupAction("Song book / Song number", filters, m_groupByActions);
  connect(actionBookNumber, SIGNAL(triggered(const KwSongdbFilterLevelList*)), this, SLOT(groupBy(const KwSongdbFilterLevelList*)));

  filters = new KwSongdbFilterLevelList;
  KwSongdbTreeGroupAction* actionLabelNameVersion = new KwSongdbTreeGroupAction("Label / Song name / Version", filters, m_groupByActions);
  //connect(actionLabelNameVersion, SIGNAL(triggered(const KwSongdbFilterLevelList*)), this, SLOT(groupBy(const KwSongdbFilterLevelList*)));

  actionNameVersion->trigger();

  // setup filter
  setModel(m_model);
}

/// Destructor.
KwSongdbTree::~KwSongdbTree()
{
}

/*
 * Actions
 */

/// Get the group by actions.
QActionGroup* KwSongdbTree::groupByActions()
{
  return m_groupByActions;
}

/*
 * Private slots
 */

/// Activate a grouping.
void KwSongdbTree::groupBy(const KwSongdbFilterLevelList* filters)
{
  m_model->setRootNode(new KwSongdbFilterNode(filters, "", 0));
}

