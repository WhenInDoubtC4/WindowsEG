#include "InternetExplorerUI.h"
#include "ui_InternetExplorerUI.h"

InternetExplorerUI::InternetExplorerUI(QWidget* parent) : QMainWindow(parent)
  , _ui(new Ui::InternetExplorerUI)
{	
	_ui->setupUi(this);

	show();
}
