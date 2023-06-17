## Qt实现编码器(飞梭)焦点逻辑

Qt本身没有一套官方的编码器焦点逻辑，网络上相关信息较少，做个简单实现。代码中飞梭的操作通过重载event()函数监听键盘事件用A、D、Enter三个键代替。

### 基本介绍

维护一个页面焦点列表的队列，通过对页面进行分级、对页面内可上焦点的控件进行集中管理，利用showEvent和hideEvent对焦点控件列表进行出入队，实现焦点策略。主窗口焦点列表始终在队首，顶层窗口焦点列表始终在队尾。

飞梭的业务逻辑主要分为两类：一是飞梭本身的业务逻辑，即焦点选择；二是控件的业务逻辑，即参数加减和点击事件。实现上通过两个类对飞梭业务进行区分。ShuttleBase类定义三个虚函数，需要焦点控件去实现的控件业务类型；ShuttleHelper类为飞梭本身业务逻辑的实现，包含了注册、删除和更新活动窗口控件列表、焦点选择或参数调节。

### 两个类

#### **ShuttleBase**类

该类为虚基类，是所有需要飞梭焦点控件的基类，定义了ShuttleClicked()、ShuttleAdd()、ShuttleReduce()三个函数，ShuttleClicked()函数为纯虚函数，其子类必须实现飞梭点击的业务逻辑，ShuttleAdd()和ShuttleReduce()函数为虚函数，分别实现参数的加减业务，默认函数体为空，根据需要重载。

#### **ShuttleHelper**类

飞梭转动及点击时间的业务实现类，同时也时对界面焦点控件进行管理的类，所有需要进行焦点遍历的控件都必须注册到该类中。该类为单例。

##### **成员变量**

(1)static ShuttleHelper *s_instance;

类唯一实例的指针。

(2) bool m_adjustFlag;

调节标志，为true时对控件参数进行调节，为false时对该窗口焦点进行遍历，默认为false。

(3) bool m_clickFlag;

焦点标记，为true时焦点处于显示状态，为false时焦点处于隐藏状态，默认为false。当界面出现点击事件后，该标志位应该置为false，再次使用飞梭标志置为true。

(4) QQueue<ShuttleData> m_shuttleQueue;

保存注册的焦点控件指针的容器，每个页面都应该是一个单独的数据成员。

##### **业务成员函数**

(1) void RegeisterNewWindow(QVector<QWidget*>, QVector<QWidget*>::const_iterator);

注册新页面，对传入的焦点控件进行变量，迭代器指向当前的焦点控件。该函数应该在窗口显示时调用。

(2) void RegeisterVoidTop();

应对特殊情况，先构建一个空的焦点列表进行占位，然后利用UpdateTopWindow填充焦点列表。该函数应该在窗口显示时调用。

(3)void UpdateTopWindow(QVector<QWidget*>, QVector<QWidget*>::const_iterator);

对顶部窗口（队尾焦点列表）进行更新。

(4) void PopTopWindow();

删除顶层窗口的焦点列表。该函数应该在窗口隐藏时调用。

(5) void UpdateMainWindow(QVector<QWidget*>, QVector<QWidget*>::const_iterator);

更新主界面焦点列表。主界面焦点列表跟随设置、模式的不同会有变化，而此时主窗口可能并不处于顶层窗口。

(6) void UpdateTopWinIter(QWidget *);

更新顶层窗口焦点，当出现鼠标点击事件时，焦点跟随鼠标移动。

(7) void SetAdjustFlag(bool flag = true);

设置调节标志。默认形参值为true，即调节标志打开，此时编码器的旋转将调用ShuttleAdd()或ShuttleReduce()对参数进行调节；形参值为false时，调节标志关闭，此时编码器的旋转将对焦点列表进行遍历。

(8) void SetClickFlag();

设置鼠标点击标记。设置鼠标点击标记后将会隐藏界面上的焦点高亮，当界面出现鼠标点击事件后应该调用该函数。

##### **公有槽函数**

(1) void onLeft();

编码器的左旋响应，根据调节标志的不同实现焦点左移或参数减小（->）操作。

(2) void onRight();

编码器的右旋响应，根据调节标志的不同实现焦点右移或参数增加（<-）操作。

(3) void onEnter();

编码器的点击响应，将直接调用ShuttleBase中的ShuttleClicked()函数，具体业务逻辑由调用控件实现。