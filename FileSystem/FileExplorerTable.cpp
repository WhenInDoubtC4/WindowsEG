#include "FileExplorerTable.h"

#include <QDebug>

FileExplorerTable::FileExplorerTable(QWidget* parent) : QTableWidget(parent)
  , _fileSystem(new QDir())
{
	horizontalHeader()->hide();
	verticalHeader()->hide();
	setShowGrid(false);
	setSelectionMode(QAbstractItemView::NoSelection);
}

FileExplorerTable::~FileExplorerTable()
{
	delete _fileSystem;
}

void FileExplorerTable::resizeEvent(QResizeEvent* event)
{
	QAbstractItemView::resizeEvent(event);

	layout();
}

void FileExplorerTable::setRoot(const QString& path, QDir::Filter filter)
{
	_fileSystem->setPath(path);
	_filter = filter;

	layout();
}

void FileExplorerTable::cdUp()
{
	//Make sure it doesn't get past the fake root
	if (_fileSystem->path() == _path) return;

	_fileSystem->cdUp();
	layout();
}

void FileExplorerTable::layout()
{
	clear();
	_icons.clear();

	QList<QFileInfo> entries = _fileSystem->entryInfoList(_filter);
	for (QFileInfo entry : qAsConst(entries))
	{
		//Filter out entries without a valid name
		if (Q_UNLIKELY(entry.baseName() == "")) continue;

		if (entry.isDir())
		{
			auto icon = new ListIcon(QPixmap(":/Resources/Style/Assets/Icons/Warning.ico"), entry.baseName());
			icon->setCorrespondingPath(_fileSystem->path() + "/" + entry.baseName());

			QObject::connect(icon, &ListIcon::opened, [=]
			{
				_fileSystem->cd(icon->getCorrespondingPath());
				layout();
			});

			_icons.push_front(icon);
		}
	}

	int rows = qFloor(sizeHint().height() / cellHeight);
	int cols = qFloor(_icons.size() / rows);
	if (_icons.size() % rows > 0) cols++;

	setRowCount(rows);
	setColumnCount(cols);

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (_icons.isEmpty()) break;

			ListIcon* nextIcon = _icons.takeLast();
			setCellWidget(r, c, nextIcon);
		}
	}
}
