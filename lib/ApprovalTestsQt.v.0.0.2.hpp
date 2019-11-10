// ApprovalTestsQt version v.0.0.2
// More information at: https://github.com/approvals/ApprovalTests.cpp.Qt
#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QApplication>
#include <QColor>
#include <QTest>
#include <QStringBuilder>
 // ******************** From: LoadApprovals.h
#ifndef APPROVALTESTS_CPP_QT_LOADAPPROVALS_H
#define APPROVALTESTS_CPP_QT_LOADAPPROVALS_H




// <SingleHpp unalterable>
#if defined(APPROVALS_CATCH_QT)
    #define CATCH_CONFIG_RUNNER
    #include <Catch.hpp>
    #define APPROVALS_CATCH_EXISTING_MAIN
#endif

#include "ApprovalTests.hpp"
// </SingleHpp>

#endif 

 // ******************** From: QTableViewWriter.h
#ifndef APPROVALTESTS_CPP_QT_QTABLEVIEWWRITER_H
#define APPROVALTESTS_CPP_QT_QTABLEVIEWWRITER_H



namespace ApprovalTestsQt
{
    class QTableViewWriter : public ApprovalTests::ApprovalWriter
    {
    public:
        explicit QTableViewWriter(const QTableView& tableWidget,
            std::string fileExtensionWithDot = ".tsv")
            : tableWidget_(tableWidget),
              fileExtensionWithDot_(fileExtensionWithDot)
        {
        }

        std::string getFileExtensionWithDot() const override
        {
            return fileExtensionWithDot_;
        }

        void write(std::string path) const override
        {
            
            QFile file(QString::fromStdString(path));

            QString separator("\t");
            QAbstractItemModel* model = tableWidget_.model();
            if (file.open(QFile::WriteOnly | QFile::Truncate))
            {
                QTextStream data(&file);
                QStringList strList;
                for (int i = 0; i < model->columnCount(); i++)
                {
                    QVariant variant =
                        model->headerData(i, Qt::Horizontal, Qt::DisplayRole);
                    strList.append(quoteString(variant));
                }
                data << strList.join(separator) << "\n";
                for (int i = 0; i < model->rowCount(); i++)
                {
                    strList.clear();
                    for (int j = 0; j < model->columnCount(); j++)
                    {
                        QVariant variant = model->data(model->index(i, j));
                        strList.append(quoteString(variant));
                    }
                    data << strList.join(separator) + "\n";
                }
                file.close();
            }
            else
            {
                throw std::runtime_error("Unable to table write to file " + path);
            }
        }

        void cleanUpReceived(std::string receivedPath) const override
        {
            remove(receivedPath.c_str());
        }

    private:
        QString quoteString(const QVariant& data) const
        {
            if (data.toString().length() > 0)
                return "\"" + data.toString() + "\"";
            else
                return "";
        }

    private:
        const QTableView& tableWidget_;
        std::string fileExtensionWithDot_;
    };
} 

#endif 

 // ******************** From: QImageApprovalWriter.h
#ifndef APPROVALTESTS_CPP_QT_QIMAGEAPPROVALWRITER_H
#define APPROVALTESTS_CPP_QT_QIMAGEAPPROVALWRITER_H



namespace ApprovalTestsQt
{
    class QImageApprovalWriter : public ApprovalTests::ApprovalWriter
    {
    public:
        explicit QImageApprovalWriter(
            QImage image, std::string fileExtensionWithDot = ".png")
            : image_(image), fileExtensionWithDot_(fileExtensionWithDot)
        {
        }

        std::string getFileExtensionWithDot() const override
        {
            return fileExtensionWithDot_;
        }

        void write(std::string path) const override
        {
            
            image_.save(QString::fromStdString(path));
        }

        void cleanUpReceived(std::string receivedPath) const override
        {
            remove(receivedPath.c_str());
        }

    private:
        QImage image_;
        std::string fileExtensionWithDot_;
    };
} 

#endif 

 // ******************** From: ApprovalsQt.h
#ifndef APPROVALTESTS_CPP_QT_APPROVALSQT_H
#define APPROVALTESTS_CPP_QT_APPROVALSQT_H


namespace ApprovalTestsQt
{
    inline void verifyQImage(const QImage& image,
        const ApprovalTests::Reporter& reporter = ApprovalTests::DiffReporter())
    {
        QImageApprovalWriter image_writer(image);
        ApprovalTests::Approvals::verify(image_writer, reporter);
    }

    inline void verifyQTableView(const QTableView& tableWidget,
        const ApprovalTests::Reporter& reporter = ApprovalTests::DiffReporter())
    {
        QTableViewWriter table_writer(tableWidget);
        ApprovalTests::Approvals::verify(table_writer, reporter);
    }
} 

#endif 

 // ******************** From: QImageApprovalComparator.h
#ifndef APPROVALTESTS_CPP_QT_QIMAGEAPPROVALCOMPARATOR_H
#define APPROVALTESTS_CPP_QT_QIMAGEAPPROVALCOMPARATOR_H


namespace ApprovalTestsQt
{
    class QImageApprovalComparator : public ApprovalTests::ApprovalComparator
    {
    public:
        bool contentsAreEquivalent(
            std::string receivedPath, std::string approvedPath) const override
        {
            const QImage receivedImage(QString::fromStdString(receivedPath));
            const QImage approvedImage(QString::fromStdString(approvedPath));
            return receivedImage == approvedImage;
        }
    };
} 

#endif 

 // ******************** From: Catch2QtApprovals.h
#ifndef APPROVALTESTS_CPP_QT_CATCH2QTAPPROVALS_H
#define APPROVALTESTS_CPP_QT_CATCH2QTAPPROVALS_H

#if defined(APPROVALS_CATCH_QT)


int main(int argc, char* argv[])
{
    
    
    
    
    QApplication app(argc, argv);

    
    
    
    
    auto pngComparatorDisposer =
        ApprovalTests::FileApprover::registerComparatorForExtension(".png",
            std::make_shared<ApprovalTestsQt::QImageApprovalComparator>());

    
    int result = Catch::Session().run(argc, argv);

    
    return result;
}
#endif 

#endif 

 // ******************** From: Catch2QtStringMaker.h
#ifndef APPROVALTESTS_CPP_QT_CATCH2QTSTRINGMAKER_H
#define APPROVALTESTS_CPP_QT_CATCH2QTSTRINGMAKER_H

#ifdef CATCH_VERSION_MAJOR

namespace Catch
{
    template <> struct StringMaker<QColor>
    {
        static std::string convert(QColor const& color)
        {
            
            const QString result = "(" %
                                   QString::number(color.redF()) % ", " %
                                   QString::number(color.greenF()) % ", " %
                                   QString::number(color.blueF()) %
                                   "), alpha = " %
                                   QString::number(color.alphaF(), 'g', 20);
            
            return result.toStdString();
        }
    };

    
    
    template <class QtCoreType> struct StringMaker<QtCoreType>
    {
        static std::string convert(QtCoreType const& object)
        {
            return QTest::toString(object);
        }
    };

    template <> struct StringMaker<QString>
    {
        static std::string convert(QString const& string)
        {
            return string.toStdString();
        }
    };
} 
#endif 

#endif 

