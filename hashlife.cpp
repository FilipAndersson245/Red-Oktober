#include "hashlife.h"
#include "ui_hashlife.h"
// demo restricts level loading to 10x10 grid size //
#define DEMO 1
#define ROOTDIR ":/levels/"
// how many levels of each grid and difficulty do we have //
#define NOOFLEVELS 4

Hashlife::Hashlife(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hashlife)
{
    ui->setupUi(this);
    _mainScene = new QGraphicsScene();
    _mainScene->setSceneRect(QRectF(0, 0, WINDOWSIZE, WINDOWSIZE));
    ui->_graphicsView->setScene(_mainScene);
    ui->_graphicsView->show();
    ui->_graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->menuBar->hide();
    autoScaleView();
    addMenuGraphics();
}

void Hashlife::addMenuGraphics()
{
    _btnNewGame = new QPushButton;
    _btnNewGame->setGeometry(QRect(40, 10, 120, 50));
    _btnNewGame->setText("New Game");
    _btnNewGame->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _proxyNewGame = new QGraphicsProxyWidget;
    _proxyNewGame = _mainScene->addWidget(_btnNewGame);
    connect(_btnNewGame, SIGNAL(released()), this, SLOT(setupGame()));
    _btnHelp = new QPushButton;
    _btnHelp->setGeometry(QRect(40, 75, 120, 50));
    _btnHelp->setText("Help");
    _btnHelp->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _proxyHelp = new QGraphicsProxyWidget;
    _proxyHelp = _mainScene->addWidget(_btnHelp);
    connect(_btnHelp, SIGNAL(released()), this, SLOT(help()));
    _btnExit = new QPushButton;
    _btnExit->setGeometry(QRect(40, 140, 120, 50));
    _btnExit->setText("Exit");
    _btnExit->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _proxyExit = new QGraphicsProxyWidget;
    _proxyExit = _mainScene->addWidget(_btnExit);
    connect(_btnExit, SIGNAL(released()), this, SLOT(exit()));
}

void Hashlife::newGame()
{
    _logic = new GameLogic(_gridSizeSelection);
    int gridSizePref = 0;
    int difficultyPref = 0;
    if (_btnEasy->isChecked())
    {
        difficultyPref = 1;
    }
    else if (_btnMedium->isChecked())
    {
        difficultyPref = 2;
    }
    else if (_btnHard->isChecked())
    {
        difficultyPref = 3;
    }
    /// DEMO VARIABLE TO ONLY LOAD 10x10 MAPS ///
    if (DEMO == 1)
    {
        gridSizePref = 1;
    }
    else if (_btnGrid10->isChecked())
    {
        gridSizePref = 1;
    }
    else if(_btnGrid15->isChecked())
    {
        gridSizePref = 2;
    }
    else if(_btnGrid20->isChecked())
    {
        gridSizePref = 3;
    }
    _mainScene->removeItem(_btnGrid10->graphicsProxyWidget());
    _mainScene->removeItem(_btnGrid15->graphicsProxyWidget());
    _mainScene->removeItem(_btnGrid20->graphicsProxyWidget());
    _mainScene->removeItem(_btnEasy->graphicsProxyWidget());
    _mainScene->removeItem(_btnMedium->graphicsProxyWidget());
    _mainScene->removeItem(_btnHard->graphicsProxyWidget());
    _mainScene->removeItem(_btnStart->graphicsProxyWidget());
    _mainScene->removeItem(_btnReturn->graphicsProxyWidget());
    _mainScene->removeItem(_difficultyLabel->graphicsProxyWidget());
    _mainScene->removeItem(_gridLabel->graphicsProxyWidget());
    _mainScene->removeItem(_boardLabel->graphicsProxyWidget());
    _mainScene->removeItem(_comboGridLabel->graphicsProxyWidget());
    _mainScene->removeItem(_comboDifficultyLabel->graphicsProxyWidget());
    _mainScene->removeItem(_boardSelector->graphicsProxyWidget());
    ui->menuBar->show();
    ui->_graphicsView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
    qDebug() << "new game";
    try
    {
        chosenMap();

    }catch(QString ERRORCODE)
    {QErrorMessage fileProblem(this); fileProblem.showMessage(ERRORCODE); fileProblem.exec();}
    setupGameGraphics();
}

void Hashlife::help()
{
    qDebug() << "seek help";
    const int width = 520;
    const int height = 800;
    const int marginLeft = 10;
    const int marginRight = 20;
    QDialog* helpDialog = new QDialog();
    helpDialog->setFixedSize(QSize(width,height));
    helpDialog->setStyleSheet("background-color:#ffffff;");
    QLabel gifExplain(helpDialog);
    QMovie *pictureGif = new QMovie(":/gitgud.gif");
    gifExplain.setMovie(pictureGif);
    pictureGif->setScaledSize(QSize(width-marginRight,width-marginRight));
    pictureGif->start();
    gifExplain.setGeometry(marginLeft,0,width-marginRight,width-marginRight);
    QLabel ruleLabel("Rules:\n"
                     "- You Play the game by connecting nodes together\n"
                     "   - You Select a node by hovering over it and selecting one of the \n"
                     "     valid bridges \n"
                     "- NodeLines must not cross each other \n"
                     "- There can be between 0-2 bridges to each node \n"
                     "- bridges can only be vertical/horizental \n"
                     "- All nodes need to be connected, can only be 1 island",
                     helpDialog);
    ruleLabel.setFont(QFont("Helvetica", 12, QFont::Bold, false));
    ruleLabel.setGeometry(marginLeft,width+10,width-marginRight,height-width-120);
    helpDialog->exec();
}

void Hashlife::exit()
{
    qApp->exit();
}

void Hashlife::returnToMenu()
{
    qDebug() << "Return";
    _mainScene->removeItem(_btnGrid10->graphicsProxyWidget());
    _mainScene->removeItem(_btnGrid15->graphicsProxyWidget());
    _mainScene->removeItem(_btnGrid20->graphicsProxyWidget());
    _mainScene->removeItem(_btnEasy->graphicsProxyWidget());
    _mainScene->removeItem(_btnMedium->graphicsProxyWidget());
    _mainScene->removeItem(_btnHard->graphicsProxyWidget());
    _mainScene->removeItem(_btnStart->graphicsProxyWidget());
    _mainScene->removeItem(_btnReturn->graphicsProxyWidget());
    _mainScene->removeItem(_difficultyLabel->graphicsProxyWidget());
    _mainScene->removeItem(_gridLabel->graphicsProxyWidget());
    _mainScene->removeItem(_boardLabel->graphicsProxyWidget());
    _mainScene->removeItem(_comboGridLabel->graphicsProxyWidget());
    _mainScene->removeItem(_comboDifficultyLabel->graphicsProxyWidget());
    _mainScene->removeItem(_boardSelector->graphicsProxyWidget());
    addMenuGraphics();
}

void Hashlife::difficultyClicked()
{
    qDebug() << "Difficulty button was clicked";
    _boardSelector->setCurrentIndex(0);
    switch(_grpDifficulty->checkedId())
    {
    case 0:
        _comboDifficultyLabel->setText("Easy:");
        break;
    case 1:
        _comboDifficultyLabel->setText("Medium:");;
        break;
    case 2:
        _comboDifficultyLabel->setText("Hard:");;
        break;
    default:
        break;
    }
}

void Hashlife::gridClicked()
{
    qDebug() << "Grid button was clicked" << _grpGridSize->checkedId();
    _boardSelector->setCurrentIndex(0);
    switch(_grpGridSize->checkedId())
    {
    case 0:
        _gridSizeSelection = 9;
        _comboGridLabel->setText("9 x 9:");
        break;
    case 1:
        _gridSizeSelection = 13;
        _comboGridLabel->setText("13 x 13:");;
        break;
    case 2:
        _gridSizeSelection = 17;
        _comboGridLabel->setText("17 x 17:");;
        break;
    default:
        break;
    }
}

void Hashlife::setupGameGraphics()
{
    _logic->addGameGraphics(_mainScene);
}

void Hashlife::resizeEvent(QResizeEvent *event)
{
    autoScaleView();
}

void Hashlife::showEvent(QShowEvent *event)
{
    ui->_graphicsView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
}

void Hashlife::autoScaleView()
{
    ui->_graphicsView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
}

Hashlife::~Hashlife()
{

}


void Hashlife::setupGame()
{
    _mainScene->removeItem(_btnNewGame->graphicsProxyWidget());
    _mainScene->removeItem(_btnHelp->graphicsProxyWidget());
    _mainScene->removeItem(_btnExit->graphicsProxyWidget());
    qDebug() << "Tried to create game";
    _btnReturn = new QPushButton;
    _btnReturn->setGeometry(QRect(160, 0, 40, 15));
    _btnReturn->setText("Return");
    _btnReturn->setFont(QFont("Helvetica", 6, QFont::Bold, true));;
    _btnReturn->setMaximumSize(40, 15);
    _proxyReturn = new QGraphicsProxyWidget;
    _proxyReturn = _mainScene->addWidget(_btnReturn);



    connect(_btnReturn, SIGNAL(clicked()), this, SLOT(returnToMenu()));



    _gridLabel = new QLabel;
    _gridLabel->setText("Select Grid Size:");
    _gridLabel->setFont(QFont("Helvetica", 4, QFont::Bold, false));
    _gridLabel->setGeometry(QRect(79, 10, 50, 10));
    _gridLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyGridLabel = new QGraphicsProxyWidget;
    _proxyGridLabel = _mainScene->addWidget(_gridLabel);

    _btnGrid10 = new QPushButton;
    _btnGrid10->setGeometry(QRect(30, 20, 40, 40));
    _btnGrid10->setText("9 x 9");
    _btnGrid10->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnGrid10->setCheckable(true);
    _btnGrid10->setChecked(true);
    _btnGrid10->setMaximumSize(40, 40);
    _proxyGrid10 = new QGraphicsProxyWidget;
    _proxyGrid10 = _mainScene->addWidget(_btnGrid10);
    _btnGrid15 = new QPushButton;
    _btnGrid15->setGeometry(QRect(80, 20, 40, 40));
    _btnGrid15->setText("13 x 13");
    _btnGrid15->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnGrid15->setCheckable(true);
    _btnGrid15->setMaximumSize(40, 40);
    _proxyGrid15 = new QGraphicsProxyWidget;
    _proxyGrid15 = _mainScene->addWidget(_btnGrid15);
    _btnGrid20 = new QPushButton;
    _btnGrid20->setGeometry(QRect(130, 20, 40, 40));
    _btnGrid20->setText("17 x 17");
    _btnGrid20->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnGrid20->setCheckable(true);
    _btnGrid20->setMaximumSize(40, 40);
    _proxyGrid20 = new QGraphicsProxyWidget;
    _proxyGrid20 = _mainScene->addWidget(_btnGrid20);

    _difficultyLabel = new QLabel;
    _difficultyLabel->setText("Select Difficulty:");
    _difficultyLabel->setFont(QFont("Helvetica", 4, QFont::Bold, false));
    _difficultyLabel->setGeometry(QRect(78, 60, 50, 10));
    _difficultyLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyDifficultyLabel = new QGraphicsProxyWidget;
    _proxyDifficultyLabel = _mainScene->addWidget(_difficultyLabel);


    _btnEasy = new QPushButton;
    _btnEasy->setGeometry(QRect(30, 70, 40, 40));
    _btnEasy->setText("Easy");
    _btnEasy->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnEasy->setCheckable(true);
    _btnEasy->setChecked(true);
    _btnEasy->setMaximumSize(40, 40);
    _proxyEasy = new QGraphicsProxyWidget;
    _proxyEasy = _mainScene->addWidget(_btnEasy);
    _btnMedium = new QPushButton;
    _btnMedium->setGeometry(QRect(80, 70, 40, 40));
    _btnMedium->setText("Medium");
    _btnMedium->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnMedium->setCheckable(true);
    _btnMedium->setMaximumSize(40, 40);
    _proxyMedium = new QGraphicsProxyWidget;
    _proxyMedium = _mainScene->addWidget(_btnMedium);
    _btnHard = new QPushButton;
    _btnHard->setGeometry(QRect(130, 70, 40, 40));
    _btnHard->setText("Hard");
    _btnHard->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnHard->setCheckable(true);
    _btnHard->setMaximumSize(40, 40);
    _proxyHard = new QGraphicsProxyWidget;
    _proxyHard = _mainScene->addWidget(_btnHard);
    _btnStart = new QPushButton;
    _btnStart->setGeometry(QRect(40, 140, 120, 50));
    _btnStart->setText("Start Game");
    _btnStart->setFont(QFont("Helvetica", 6, QFont::Bold, true));;
    _proxyStart = new QGraphicsProxyWidget;
    _proxyStart = _mainScene->addWidget(_btnStart);
    connect(_btnStart, SIGNAL(clicked()), this, SLOT(newGame()));

    _boardLabel = new QLabel;
    _boardLabel->setText("Select Game Board:");
    _boardLabel->setFont(QFont("Helvetica", 4, QFont::Bold, false));
    _boardLabel->setGeometry(QRect(76, 110, 50, 10));
    _boardLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyBoardLabel = new QGraphicsProxyWidget;
    _proxyBoardLabel = _mainScene->addWidget(_boardLabel);

    _comboDifficultyLabel = new QLabel;
    _comboDifficultyLabel->setText("Easy:");
    _comboDifficultyLabel->setFont(QFont("Helvetica", 4, QFont::Bold, false));
    _comboDifficultyLabel->setGeometry(QRect(52, 121, 30, 10));
    _comboDifficultyLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyComboDifficultyLabel = new QGraphicsProxyWidget;
    _proxyComboDifficultyLabel = _mainScene->addWidget(_comboDifficultyLabel);

    _comboGridLabel = new QLabel;
    _comboGridLabel->setText("9 x 9:");
    _comboGridLabel->setFont(QFont("Helvetica", 4, QFont::Bold, false));
    _comboGridLabel->setGeometry(QRect(30, 121, 30, 10));
    _comboGridLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyComboGridLabel = new QGraphicsProxyWidget;
    _proxyComboGridLabel = _mainScene->addWidget(_comboGridLabel);

    _grpGridSize = new QButtonGroup;
    _grpGridSize->addButton(_btnGrid10, 0);
    _grpGridSize->addButton(_btnGrid15, 1);
    _grpGridSize->addButton(_btnGrid20, 2);

    connect(_grpGridSize, SIGNAL(buttonClicked(int)), this, SLOT(gridClicked()));

    _grpDifficulty = new QButtonGroup;
    _grpDifficulty->addButton(_btnEasy, 0);
    _grpDifficulty->addButton(_btnMedium, 1);
    _grpDifficulty->addButton(_btnHard, 2);

    connect(_grpDifficulty, SIGNAL(buttonClicked(int)), this, SLOT(difficultyClicked()));



    _boardSelector = new QComboBox;
    _boardSelector->setGeometry(QRect(75, 120, 95, 12));
    _boardSelector->setFont(QFont("Helvetica", 4, QFont::Bold, false));
    _boardSelector->setMaximumSize(95, 12);
    _boardSelector->insertItem(0, "Random Online");
    _boardSelector->insertItem(1, "Level 1");
    _boardSelector->insertItem(2, "Level 2");
    _boardSelector->insertItem(3, "Level 3");
    _boardSelector->insertItem(4, "Level 4");
    _boardSelector->insertItem(5, "Level 5");
    _boardSelector->insertItem(6, "Level 6");
    _boardSelector->insertItem(7, "Level 7");
    _boardSelector->setIconSize(QSize(3, 3));
    _proxyBoardSelector = new QGraphicsProxyWidget;
    _proxyBoardSelector = _mainScene->addWidget(_boardSelector);

}

void Hashlife::on_actionEnd_Game_triggered()
{
    _mainScene->clear();
    _logic->endGame();
    addMenuGraphics();
}

void Hashlife::on_actionHelp_triggered()
{
    help();
}

//Creates a string to the location of the target file based on player choices
void Hashlife::chosenMap()
{
    QString loadThisTypeOfBoard = ROOTDIR;
    switch (_grpGridSize->checkedId())
    {
    case 0:
        loadThisTypeOfBoard.append("9x9/");
        break;
    case 1:
        loadThisTypeOfBoard.append("13x13/");
        break;
    case 2:
        loadThisTypeOfBoard.append("17x17/");
        break;
        // Never end up here //
    default:
        throw(QString ("something went wrong while computing user lever choice"));
    }
    switch (_grpDifficulty->checkedId())
    {
    case 0:
        loadThisTypeOfBoard.append("easy/");
        break;
    case 1:
        loadThisTypeOfBoard.append("medium/");
        break;
    case 2:
        loadThisTypeOfBoard.append("hard/");
        break;
        // Never end up here //
    default:
        throw(QString ("something went wrong while computing user lever choice"));
    }

    if (!loadThisTypeOfBoard.isEmpty())
    {
        int random = returnRandom();
        switch(_boardSelector->currentIndex())
        {
        case 0: //Load random level
            loadThisTypeOfBoard.append("level1.hashiboard");;
            break;
        case 1:
            loadThisTypeOfBoard.append("level1.hashiboard");;
            break;
        case 2:
            loadThisTypeOfBoard.append("level2.hashiboard");;;
            break;
        case 3:
            loadThisTypeOfBoard.append("level3.hashiboard");;;
            break;
        case 4:
            loadThisTypeOfBoard.append("level4.hashiboard");;;
            break;
        case 5:
            loadThisTypeOfBoard.append("level5.hashiboard");;;
            break;
        case 6:
            loadThisTypeOfBoard.append("level6.hashiboard");;;
            break;
        case 7:
            loadThisTypeOfBoard.append("level7.hashiboard");;;
            break;
        default:
            break;
        }
        qDebug() << "User level choice:" << loadThisTypeOfBoard;
        _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
    }
}

int Hashlife::returnRandom(void)
{
    srand((int)time(NULL));
    return (rand() % 7) + 1;
}
