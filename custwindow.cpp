#include "custwindow.h"
#include "ui_custwindow.h"

#include <QtSql>

CustWindow::CustWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustWindow)
{
    ui->setupUi(this);
    ui->custTable->addAction(ui->insertRowAction);
    ui->custTable->addAction(ui->deleteRowAction);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(this, tr("错误"), tr("没有数据库驱动"));

    // connect the database
    QSqlError err = contDB();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

    // Create the data custMod
    custMod = new QSqlRelationalTableModel(ui->custTable);
    custMod->setEditStrategy(QSqlTableModel::OnFieldChange);
    custMod->setTable("cust_table");

    // Remember the indexes of the columns
    areaIdx = custMod->fieldIndex("area_name");
    cateIdx = custMod->fieldIndex("cate_name");
    mainLevIdx = custMod->fieldIndex("main_name");
    mainPepIdx = custMod->fieldIndex("main_people");
    posIdx = custMod->fieldIndex("pos_name");
    genderIdx = custMod->fieldIndex("gender");

    // Set the relations to the other database tables
    /*
    custMod->setRelation(areaIdx, QSqlRelation("area", "id", "name"));
    custMod->setRelation(cateIdx, QSqlRelation("category", "id", "name"));
    custMod->setRelation(mainLevIdx, QSqlRelation("main_lev", "id", "name"));
    custMod->setRelation(mainPepIdx, QSqlRelation("main_pep", "id", "name"));
    custMod->setRelation(posIdx, QSqlRelation("position", "id", "name"));
    */
    custMod->setRelation(genderIdx, QSqlRelation("gender", "id", "name"));

    // Set the localized header captions
    custMod->setHeaderData(areaIdx, Qt::Horizontal, tr("区域"));
    custMod->setHeaderData(cateIdx, Qt::Horizontal, tr("类别"));
    custMod->setHeaderData(mainLevIdx, Qt::Horizontal, tr("维护等级"));
    custMod->setHeaderData(mainPepIdx, Qt::Horizontal, tr("维护人"));
    custMod->setHeaderData(posIdx, Qt::Horizontal, tr("职务"));
    custMod->setHeaderData(genderIdx, Qt::Horizontal, tr("性别"));
    custMod->setHeaderData(custMod->fieldIndex("usr_name"), Qt::Horizontal, tr("姓名"));
    custMod->setHeaderData(custMod->fieldIndex("in_time"), Qt::Horizontal, tr("入库时间"));
    custMod->setHeaderData(custMod->fieldIndex("contact"), Qt::Horizontal, tr("联系方式"));
    custMod->setHeaderData(custMod->fieldIndex("unit_addr"), Qt::Horizontal, tr("工作单位"));
    custMod->setHeaderData(custMod->fieldIndex("home_addr"), Qt::Horizontal, tr("家庭住址"));
    custMod->setHeaderData(custMod->fieldIndex("birth_date"), Qt::Horizontal, tr("出生年月"));

    // Populate the custMod
    if (!custMod->select()) {
        showError(custMod->lastError());
        return;
    }

    // Set the custMod and hide the ID column
    ui->custTable->setModel(custMod);
    ui->custTable->setItemDelegate(new QSqlRelationalDelegate(ui->custTable));
    ui->custTable->setColumnHidden(custMod->fieldIndex("usr_id"), true);
    ui->custTable->setColumnHidden(custMod->fieldIndex("visit_rec"), true);
    ui->custTable->setColumnHidden(custMod->fieldIndex("main_rec"), true);
    ui->custTable->setColumnHidden(custMod->fieldIndex("pres_rec"), true);
    ui->custTable->setColumnHidden(custMod->fieldIndex("area"), true);
    ui->custTable->setColumnHidden(custMod->fieldIndex("position"), true);
    ui->custTable->setColumnHidden(custMod->fieldIndex("category"), true);
    ui->custTable->setColumnHidden(custMod->fieldIndex("main_lev"), true);
    ui->custTable->setColumnHidden(custMod->fieldIndex("main_pep"), true);
    ui->custTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Set column width
    ui->custTable->setColumnWidth(areaIdx,80);
    ui->custTable->setColumnWidth(cateIdx,80);
    ui->custTable->setColumnWidth(mainPepIdx,80);
    ui->custTable->setColumnWidth(posIdx,80);
    ui->custTable->setColumnWidth(custMod->fieldIndex("usr_name"),80);
    ui->custTable->resizeColumnToContents(custMod->fieldIndex("in_time"));
    ui->custTable->resizeColumnToContents(custMod->fieldIndex("birth_date"));
    ui->custTable->resizeColumnToContents(custMod->fieldIndex("contact"));
    ui->custTable->horizontalHeader()->setResizeMode(custMod->fieldIndex("unit_addr"),QHeaderView::Stretch);
    ui->custTable->horizontalHeader()->setResizeMode(custMod->fieldIndex("home_addr"),QHeaderView::Stretch);
    ui->custTable->resizeColumnToContents(genderIdx);
    ui->custTable->setCurrentIndex(custMod->index (0, 0));
}

QSqlError CustWindow::contDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("customer.db");
    if (!QFile::exists("customer.db"))
    {
        QMessageBox::critical(this, tr("错误"),
                    tr("数据库不存在！") );

        return QSqlError("QSQLITE","customer.db",QSqlError::UnknownError,-1);
    }
    if (!db.open())
    {
        return db.lastError();
    }
    else
    {
        return QSqlError();
    }
}

void CustWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, tr("失败"),
                tr("操作失败：") + err.text());
}

void CustWindow::queryTable(bool toInsert)
{
    //QMessageBox::information(this, tr("alert"),tr("alert"));

    QString queryStr("1=1 ");
    if(!toInsert)
    {
        if (ui->genCombo->currentIndex())
        {
            //custMod->setFilter(tr("AND gender=%1").arg(ui->genCombo->currentIndex() - 1));
            queryStr = queryStr + tr("AND gender=%1").arg(ui->genCombo->currentIndex() - 1);
        }
        else
        {
            //custMod->setFilter(tr("AND 1=1"));
            queryStr = queryStr + tr("AND 1=1 ");
        }
        if (!ui->nameEdit->text().trimmed().isEmpty())
        {
            //custMod->setFilter(tr("AND usr_name LIKE '%") + ui->nameEdit->text().trimmed() + tr("%'"));
            queryStr = queryStr + tr(" AND usr_name LIKE '%") + ui->nameEdit->text().trimmed() + tr("%' ");
        }

        if (!ui->posEdit->text().trimmed().isEmpty())
        {
            //custMod->setFilter(tr("AND pos_name LIKE '%") + ui->posEdit->text().trimmed() + tr("%'"));
            queryStr = queryStr + tr(" AND pos_name LIKE '%") + ui->posEdit->text().trimmed() + "%' ";
        }

        if (!ui->mainPepEdit->text().trimmed().isEmpty())
        {
            //custMod->setFilter(tr("AND main_people LIKE '%") + ui->mainPepEdit->text().trimmed() + tr("%'"));
            queryStr = queryStr + tr(" AND main_people LIKE '%") + ui->mainPepEdit->text().trimmed() + "%' ";
        }

        if (!ui->areaEdit->text().trimmed().isEmpty())
        {
            //custMod->setFilter(tr("AND area_name LIKE '%") + ui->areaEdit->text().trimmed() + tr("%'"));
            queryStr = queryStr + tr(" AND area_name LIKE '%") + ui->areaEdit->text().trimmed() + "%' ";
        }

        if (!ui->mainLevEdit->text().trimmed().isEmpty())
        {
            //custMod->setFilter(tr("AND main_name LIKE '%") + ui->mainLevEdit->text().trimmed() + tr("%'"));
            queryStr = queryStr + tr(" AND main_name LIKE '%") + ui->mainLevEdit->text().trimmed() + "%' ";
        }

        if (!ui->cateEdit->text().trimmed().isEmpty())
        {
            //custMod->setFilter(tr("AND main_name LIKE '%") + ui->mainLevEdit->text().trimmed() + tr("%'"));
            queryStr = queryStr + tr(" AND cate_name LIKE '%") + ui->cateEdit->text().trimmed() + "%' ";
        }
    }
    custMod->setFilter(queryStr);

    if (!custMod->select()) {
        showError(custMod->lastError());
        return;
    }

    if(!toInsert)
    {
        if (custMod->lastError().type() != QSqlError::NoError)
            emit statusMessage(tr("查询失败：") + custMod->lastError().text());
        else if (custMod->query().isSelect())
            emit statusMessage(tr("查询成功，共%1条记录").arg(custMod->rowCount()));
    }
    custMod->setEditStrategy(QSqlTableModel::OnFieldChange);
}

void CustWindow::insertRow()
{
    custMod->setEditStrategy(QSqlTableModel::OnRowChange);
    int rowNum = custMod->rowCount();
    int maxUsrId = 0;
    if (rowNum)
    {
        maxUsrId = custMod->data(custMod->index(rowNum - 1,0)).toInt();
    }

    custMod->database().transaction();
    custMod->insertRow(rowNum);
    custMod->setData(custMod->index(rowNum, 0),maxUsrId + 1);
    custMod->setData(custMod->index(rowNum, 2),0);
    if (custMod->submitAll())
    {
        custMod->database().commit();
        emit statusMessage(tr("插入成功"));
    }
    else
    {
        custMod->database().rollback();
        showError(custMod->lastError());
        emit statusMessage(tr("插入失败：") + custMod->lastError().text());
        return;
    }
    QModelIndex insertedIndex = custMod->index(rowNum,1);
    ui->custTable->setCurrentIndex(insertedIndex);
    ui->custTable->edit(insertedIndex);
}

void CustWindow::deleteRow()
{
    custMod->setEditStrategy(QSqlTableModel::OnManualSubmit);
    custMod->database().transaction();
    QModelIndexList currentSelection = ui->custTable->selectionModel()->selectedIndexes();
    for (int i = 0; i < currentSelection.count(); ++i) {
        if (currentSelection.at(i).column() != 0)
            continue;
        custMod->removeRow(currentSelection.at(i).row());
    }

    if (custMod->submitAll())
    {
        custMod->database().commit();
        emit statusMessage(tr("删除成功"));
    }
    else
    {
        custMod->database().rollback();
        showError(custMod->lastError());
        emit statusMessage(tr("删除失败：") + custMod->lastError().text());
        return;
    }
    custMod->setEditStrategy(QSqlTableModel::OnFieldChange);
}

CustWindow::~CustWindow()
{
    delete ui;
    delete custMod;
    db.close();
}
