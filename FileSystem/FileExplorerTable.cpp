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
	while(!_icons.isEmpty()) delete _icons.takeLast();
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
	_path = path;

	layout();
}

void FileExplorerTable::cdUp()
{
	//Make sure it doesn't get past the fake root
	if (_fileSystem->path() == _path) return;

	_fileSystem->cdUp();
	layout();

	emit dirChanged();
}

void FileExplorerTable::cd(const QString& path)
{
	if (path.length() < _fileSystem->path()) return;

	_fileSystem->cd(path);
	layout();

	emit dirChanged();
}

void FileExplorerTable::layout()
{
	//Get rid of everything in the table
	clear();
	while(!_icons.isEmpty()) delete _icons.takeLast();

	QList<QFileInfo> entries = _fileSystem->entryInfoList(_filter);
	for (QFileInfo entry : qAsConst(entries))
	{
		//Filter out entries without a valid name
		if (Q_UNLIKELY(entry.baseName() == QString())) continue;

		//Directories
		//TODO: Handle root drive and add proper icons
		if (entry.isDir())
		{
			auto icon = new ListIcon(QPixmap(":/Resources/Style/Assets/Icons/Warning.ico"), entry.baseName(), this);
			icon->setCorrespondingPath(_fileSystem->path() + "/" + entry.baseName());

			QObject::connect(icon, &ListIcon::opened, [=]
			{
				_fileSystem->cd(icon->getCorrespondingPath());
				layout();
				emit dirChanged();
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
