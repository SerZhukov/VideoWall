#include "handlerrtsp.h"
#include <iostream>
#include <QPaintEvent>
#include <QCoreApplication>
#include <QThread>
#include <QEventLoop>
#include <QTimer>


HandlerRTSP::HandlerRTSP(const std::string &rtsp, QWidget *parent) : QWidget(parent),
    rtsp_(rtsp)
{

}

HandlerRTSP::~HandlerRTSP()
{

}

void HandlerRTSP::setRTSP(const std::string& rtsp)
{
    rtsp_=rtsp;
}

void HandlerRTSP::setPlayerWindow(QWidget *playerWindow)
{
    playerWindow_= playerWindow;
}

void HandlerRTSP::play()
{
    cv::VideoCapture capture;
    capture.open(rtsp_);
    if (!capture.isOpened()) {
        qDebug() << "Ошибка: не удалось открыть RTSP поток";
        return;
    }
    cv::Mat frame;
    while (true) {
        // Чтение следующего кадра
        capture.read(frame);
        // Проверка на окончание кадров
        QImage img = mat2Image(frame);
        QRegion reg(img.rect());
        QPaintEvent event(reg);
        emit sendFrame(img);
        QCoreApplication::sendEvent(playerWindow_, &event);

        if (frame.empty())
        {
            capture.open(rtsp_);
            qDebug() << "Restart video";
            capture.read(frame);
            if(frame.empty())
            {
                qDebug() << "Reset is not successful";
                break;
            }

        }
        // Отображение кадра
        cv::imshow("RTSP Stream_1", frame);
        // Ожидание 30 мс или прерывание при нажатии клавиши
        if (cv::waitKey(30) >= 0) break;
    }
    // Освобождение ресурсов
    capture.release();
    cv::destroyAllWindows();

}

void HandlerRTSP::playVideoFrame()
{
    qDebug() << "void HandlerRTSP::playVideoFrame()";
    cv::VideoCapture capture;
    capture.open(rtsp_);
    if (!capture.isOpened()) {
        qDebug() << "Ошибка: не удалось открыть RTSP поток";
        return;
    }
    cv::Mat frame;
    while (true) {
        // Чтение следующего кадра
        capture.read(frame);
        // Проверка на окончание кадров
        QImage img = mat2Image(frame);
        QRegion reg(img.rect());
        QPaintEvent event(reg);
        emit sendFrame(img);
        qDebug() << "generate emit";
        if (frame.empty())
        {
            capture.open(rtsp_);
            qDebug() << "Restart video";
            capture.read(frame);
            if(frame.empty())
            {
                qDebug() << "Reset is not successful";
                break;
            }

        }
        //QThread::msleep(30);
        // Отображение кадра
        //cv::imshow("RTSP Stream_1", frame);
        // Ожидание 30 мс или прерывание при нажатии клавиши
        //if (cv::waitKey(30) >= 0) break;
        delay(30);

    }
    // Освобождение ресурсов
    capture.release();
    cv::destroyAllWindows();
}

QImage HandlerRTSP::mat2Image(const cv::Mat &src)
{
    cv::Mat temp; // нужно для правильного порядка каналов
    cv::cvtColor(src, temp, cv::COLOR_BGR2RGB); // конвертируем BGR в RGB
    QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits();
    return dest;
}

void HandlerRTSP::delay(int n)
{
    QEventLoop loop;
    QTimer::singleShot(n, &loop, &QEventLoop::quit);
    loop.exec();
}
