#ifndef FILE_LIST_H_
#define FILE_LIST_H_

#include "Global.hpp"

#include <QWidget>
#include <QUrl>
#include <QString>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QDragEnterEvent>
#include <QMimeData>
// #include <QTreeView>
// #include <QItemDelegate>

#include "FFMPEG.hpp"

#include "Utils.hpp"

typedef QList<QPair<CodecType, QString> > CodecStringPair ;


class FileInfo
{
public:
	FileInfo(QString filename);
	QString container (void) const;
	CodecStringPair getStreams(void) const;
private:
	FileInfo(void);
	CodecStringPair streams;
	QString container_;
};


// class ItemDelegate : public QItemDelegate
// {
// 	Q_OBJECT

// public:
// 	ItemDelegate(QWidget *parent = NULL) : QItemDelegate(parent) {};

// 	virtual QWidget *createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const ;
// 	virtual void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const ;
// 	virtual void	setEditorData ( QWidget * editor, const QModelIndex & index ) const ;
// 	virtual void	setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const ;
// 	virtual QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const ;
// 	virtual void	updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const ;
// };


namespace GUI
{

	class FileList : public QTreeWidget
	{
		Q_OBJECT
	public:
		FileList(QWidget *parent=NULL);
	protected:
		virtual void dragEnterEvent(QDragEnterEvent*) ;
		virtual void dragMoveEvent(QDragMoveEvent *);
		virtual void dropEvent(QDropEvent *);
	public slots:
		void add_file(QString path);
	};

}


#endif //FILE_LIST
