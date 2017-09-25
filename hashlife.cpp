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
    //  sendRequest();
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
    ui->menuBar->show();
    ui->_graphicsView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
    qDebug() << "new game";

    if (onlineLoad())
    {

    }

    try
    {
        int difficultyChoosen = 2;
        int boardSizeChoosen = 1;
        choosenMap(difficultyChoosen,boardSizeChoosen);

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
    addMenuGraphics();
}

void Hashlife::setupGameGraphics()
{
    _logic.addGameGraphics(_mainScene);
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
    _btnReturn->setGeometry(QRect(0, 0, 40, 15));
    _btnReturn->setText("Return");
    _btnReturn->setFont(QFont("Helvetica", 6, QFont::Bold, true));;
    _btnReturn->setMaximumSize(40, 15);
    _proxyReturn = new QGraphicsProxyWidget;
    _proxyReturn = _mainScene->addWidget(_btnReturn);
    connect(_btnReturn, SIGNAL(released()), this, SLOT(returnToMenu()));

    _btnGrid10 = new QPushButton;
    _btnGrid10->setGeometry(QRect(30, 30, 40, 40));
    _btnGrid10->setText("10 x 10");
    _btnGrid10->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnGrid10->setCheckable(true);
    _btnGrid10->setChecked(true);
    _btnGrid10->setMaximumSize(40, 40);
    _proxyGrid10 = new QGraphicsProxyWidget;
    _proxyGrid10 = _mainScene->addWidget(_btnGrid10);
    _btnGrid15 = new QPushButton;
    _btnGrid15->setGeometry(QRect(80, 30, 40, 40));
    _btnGrid15->setText("15 x 15");
    _btnGrid15->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnGrid15->setCheckable(true);
    _btnGrid15->setMaximumSize(40, 40);
    _proxyGrid15 = new QGraphicsProxyWidget;
    _proxyGrid15 = _mainScene->addWidget(_btnGrid15);
    _btnGrid20 = new QPushButton;
    _btnGrid20->setGeometry(QRect(130, 30, 40, 40));
    _btnGrid20->setText("20 x 20");
    _btnGrid20->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnGrid20->setCheckable(true);
    _btnGrid20->setMaximumSize(40, 40);
    _proxyGrid20 = new QGraphicsProxyWidget;
    _proxyGrid20 = _mainScene->addWidget(_btnGrid20);
    _btnEasy = new QPushButton;
    _btnEasy->setGeometry(QRect(30, 80, 40, 40));
    _btnEasy->setText("Easy");
    _btnEasy->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnEasy->setCheckable(true);
    _btnEasy->setChecked(true);
    _btnEasy->setMaximumSize(40, 40);
    _proxyEasy = new QGraphicsProxyWidget;
    _proxyEasy = _mainScene->addWidget(_btnEasy);
    _btnMedium = new QPushButton;
    _btnMedium->setGeometry(QRect(80, 80, 40, 40));
    _btnMedium->setText("Medium");
    _btnMedium->setFont(QFont("Helvetica", 6, QFont::Bold, true));
    _btnMedium->setCheckable(true);
    _btnMedium->setMaximumSize(40, 40);
    _proxyMedium = new QGraphicsProxyWidget;
    _proxyMedium = _mainScene->addWidget(_btnMedium);
    _btnHard = new QPushButton;
    _btnHard->setGeometry(QRect(130, 80, 40, 40));
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
    connect(_btnStart, SIGNAL(released()), this, SLOT(newGame()));

    _grpGridSize = new QButtonGroup;
    _grpGridSize->addButton(_btnGrid10, 0);
    _grpGridSize->addButton(_btnGrid15, 1);
    _grpGridSize->addButton(_btnGrid20, 2);

    _grpDifficulty = new QButtonGroup;
    _grpDifficulty->addButton(_btnEasy, 0);
    _grpDifficulty->addButton(_btnMedium, 1);
    _grpDifficulty->addButton(_btnHard, 2);





    _boardSelector = new QComboBox(this);
    _boardSelector->insertItem(0, "Random");
    _boardSelector->insertItem(1, "Board A");
    _boardSelector->insertItem(2, "Board B");
    _boardSelector->insertItem(3, "Board C");
    _boardSelector->insertItem(4, "Board D");
    _boardSelector->insertItem(5, "Board E");
    _proxyBoardSelector = new QGraphicsProxyWidget;
    _proxyBoardSelector = _mainScene->addWidget(_boardSelector);

}


void Hashlife::on_actionEnd_Game_triggered()
{
    _mainScene->clear();
    _logic.endGame();
    addMenuGraphics();
}

void Hashlife::on_actionHelp_triggered()
{
    help();
}

void Hashlife::replyFinished(QNetworkReply *reply)
{
    QString dataFromSite = "";
    if(reply->error() == QNetworkReply::NetworkError::NoError)
    {
        QByteArray readSite = reply->readAll();
        // throw away data before and after //
        for (int i = 7000; i < 11400; ++i)
        {
            dataFromSite += readSite[i];
        }
        qDebug() << "Downloaded map data from server OK!" << reply->errorString();

        // make call to parser to use this information //

        loadGameBoardFromSiteData(dataFromSite);
    }
    else
    {
        _isOnline = false;
        qDebug() << "something wrong with GET request, going offline";
    }

}
void Hashlife::choosenMap(int userDifficultyChoice, int userBoardSize)
{
    QString loadThisTypeOfBoard = ROOTDIR;
    switch (userDifficultyChoice)
    {

    case 1:
    {
        loadThisTypeOfBoard.append("EASY");
    }
        break;
    case 2:
    {
        loadThisTypeOfBoard.append("MEDIUM");
    }
        break;
    case 3:
    {
        loadThisTypeOfBoard.append("HARD");
    }
        break;
        // Never end up here //
    default:
    {
        throw(QString ("something went wrong while computing user lever choice"));
    }
    }
    switch (userBoardSize)
    {

    case 1:
    {
        loadThisTypeOfBoard.append("_10x10");
    }
        break;
    case 2:
    {
        loadThisTypeOfBoard.append("_15x15");
    }
        break;
    case 3:
    {
        loadThisTypeOfBoard.append("_20x20");
    }
        break;
        // Never end up here //
    default:
    {
        throw(QString ("something went wrong while computing user lever choice"));
    }
    }
    if (!loadThisTypeOfBoard.isEmpty())
    {
        // dot is for identification of new info //
        loadThisTypeOfBoard.append("_level" + QString::number(returnRandom()) +".hashiboard");

        qDebug() << "User level choice:" << loadThisTypeOfBoard;

        _logic.loadGameBoardFromFile(loadThisTypeOfBoard);
    }

}

void Hashlife::onlineLoad()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));


    QUrl urlToSite("http://www.menneske.no/hashi/eng/");

    QNetworkRequest request;
    request.setUrl(urlToSite);
    request.setRawHeader("Connection", "close");
    manager->get(request);
}

void Hashlife::parseSiteData(QString dataFromSite)
{
    QByteArray result = "";
    QRegularExpression checkForNode ("(ring)");
    QRegularExpression checkForBlanc ("(white)");
    QRegularExpression checkForDigit("\\d");

    QRegularExpressionMatch match;
    QRegularExpressionMatch matchBlanc;



    match = checkForNode.match(dataFromSite);
    matchBlanc = checkForBlanc.match(dataFromSite);
    qDebug() << match.lastCapturedIndex();
    for (int i= 0; i < 1000 ; ++i)
    {

        match = checkForNode.match(dataFromSite);
        matchBlanc = checkForBlanc.match(dataFromSite);

        if ((match.capturedStart() > matchBlanc.capturedStart()) && matchBlanc.hasMatch())
        {
            result.append("0");
            dataFromSite.remove(0,matchBlanc.capturedEnd());
        }

        else if ((match.capturedStart() < matchBlanc.capturedStart()) && match.hasMatch())
        {
            QString matched = match.captured(i);

            qDebug() << match.capturedStart() << match.capturedEnd();
            // take out number from it //
            qDebug() << dataFromSite.at(match.capturedEnd()+2);
            result.append(dataFromSite.at((match.capturedEnd()+2)));
            //next string to check //
            dataFromSite.remove(0,match.capturedEnd());
        }


    }


    qDebug() << "Level from site loaded " << sqrt(result.length()) << "X"  << sqrt(result.length()) << "=" << result.length() << "am i one short bitch?";

    _logic.loadLevel(result);


}
int Hashlife::returnRandom(void)
{
    srand((int)time(NULL));
    int randNum = (rand() % NOOFLEVELS) + 1;
    return randNum;
}
