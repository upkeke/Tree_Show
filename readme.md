# 模板类里面没有代码提示
一个专门为Node类型而建，可以设置一个特化版本
有约束的话，就有代码提示
# qt cmake
#设置UIC的查找路径
set(AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

qt5_wrap_ui(SOURCES mainwin.ui)
# qt 动画实现
QGraphicsItemAnimation

QGraphicsItem
https://blog.csdn.net/qq_26480033/article/details/112060590 

QAbstractAnimation 
https://blog.csdn.net/wuwenbin12/article/details/120846285

GrapNodeItem

MyGraphicsItem

GrapLineItem
@斯卡蒂 "吾名死亡之翼，天命之灭世者，",后面的完整句子

## QTimeLine控件
https://www.cnblogs.com/alex-space/p/13343049.html
 是Qt中的一个时间线控件，可以用来实现动画效果。QTimeLine控件可以通过设置总时长、分步间隔和曲线类型来控制动画效果。你可以通过调用函数来控制动画的开始、暂停、停止等操作，并且还可以使用信号槽来监听动画状态的变化

 ### QTimeLine::frameChanged 
 每隔一帧发射一次这个信号，可以用槽函数接受，做一些事情

   //动画总时间是5000毫秒
  QTimeLine *timer = new QTimeLine(5000);
  //总共的帧数 100帧
  timer->setFrameRange(0, 100);
  QGraphicsItemAnimation *animation = new QGraphicsItem

## qt属性
```c

class TempCtrl : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int m_interval READ getInterval WRITE setInterval)
public:
    int     m_interval=1;
    int     getInterval();
    void    setInterval(int _interval); 
    TempCtrl(QWidget *parent = 0);
};
//读取所有属性
    for(int i=0;i<ui->pushButton->metaObject()->propertyCount();i++)
        qDebug()<<ui->pushButton->metaObject()->property(i).name();
```

路径QPainterPath
https://haigear.blog.csdn.net/article/details/128722830?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7ERate-1-128722830-blog-109601422.pc_relevant_recovery_v2&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7ERate-1-128722830-blog-109601422.pc_relevant_recovery_v2&utm_relevant_index=1