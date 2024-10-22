//класс для обработки rtsp ссылок(используя библиотеку OpenCV) и отправки кадра

#ifndef HANDLERRTSP_H
#define HANDLERRTSP_H
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <QObject>
#include <QImage>

class HandlerRTSP : public QObject
{
    Q_OBJECT
public:
    explicit HandlerRTSP(const std::string& rtsp, QObject *parent = nullptr);
    ~HandlerRTSP();
public slots:
    void playVideoFrame();
    void setRTSP(const std::string& rtsp);
private:
    std::string rtsp_;
    QImage mat2Image(const cv::Mat& src);
    void delay(int n);
signals:
    void sendFrame(const QImage&);
};

#endif // HANDLERRTSP_H
