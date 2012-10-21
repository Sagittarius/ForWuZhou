#include "custwindow.h"
#include "ui_custwindow.h"

CustWindow::CustWindow(QString usrName, QString password, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::CustWindow)
{
    ui->setupUi(this);
    usr = usrName;
    pwd = password;
    chgPwdDiag = new ChgPwd(usr,pwd,this);
    ui->custTable->addAction(ui->insertRowAction);
    ui->custTable->addAction(ui->deleteRowAction);

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
    relationIdx = custMod->fieldIndex("relate_lev");

    // Set the relations to the other database tables
    /*
    custMod->setRelation(areaIdx, QSqlRelation("area", "id", "name"));
    custMod->setRelation(cateIdx, QSqlRelation("category", "id", "name"));
    custMod->setRelation(mainLevIdx, QSqlRelation("main_lev", "id", "name"));
    custMod->setRelation(mainPepIdx, QSqlRelation("main_pep", "id", "name"));
    custMod->setRelation(posIdx, QSqlRelation("position", "id", "name"));
    */
    custMod->setRelation(genderIdx, QSqlRelation("gender", "id", "name"));
    custMod->setRelation(relationIdx, QSqlRelation("relate_level", "id", "name"));

    // Set the localized header captions
    custMod->setHeaderData(areaIdx, Qt::Horizontal, tr("区域"));
    custMod->setHeaderData(cateIdx, Qt::Horizontal, tr("类别"));
    custMod->setHeaderData(mainLevIdx, Qt::Horizontal, tr("维护等级"));
    custMod->setHeaderData(mainPepIdx, Qt::Horizontal, tr("维护人"));
    custMod->setHeaderData(posIdx, Qt::Horizontal, tr("职务"));
    custMod->setHeaderData(genderIdx, Qt::Horizontal, tr("性别"));
    custMod->setHeaderData(custMod->fieldIndex("usr_name"), Qt::Horizontal, tr("姓名"));
    custMod->setHeaderData(custMod->fieldIndex("relate_lev"), Qt::Horizontal, tr("关系度"));
    custMod->setHeaderData(custMod->fieldIndex("specialty"), Qt::Horizontal, tr("专业"));
    custMod->setHeaderData(custMod->fieldIndex("in_time"), Qt::Horizontal, tr("入库时间"));
    custMod->setHeaderData(custMod->fieldIndex("contact"), Qt::Horizontal, tr("联系方式"));
    custMod->setHeaderData(custMod->fieldIndex("unit_addr"), Qt::Horizontal, tr("工作单位"));
    custMod->setHeaderData(custMod->fieldIndex("home_addr"), Qt::Horizontal, tr("家庭住址"));
    custMod->setHeaderData(custMod->fieldIndex("birth_date"), Qt::Horizontal, tr("出生年月"));
    custMod->setHeaderData(custMod->fieldIndex("jan"), Qt::Horizontal, tr("1"));
    custMod->setHeaderData(custMod->fieldIndex("feb"), Qt::Horizontal, tr("2"));
    custMod->setHeaderData(custMod->fieldIndex("mar"), Qt::Horizontal, tr("3"));
    custMod->setHeaderData(custMod->fieldIndex("apr"), Qt::Horizontal, tr("4"));
    custMod->setHeaderData(custMod->fieldIndex("may"), Qt::Horizontal, tr("5"));
    custMod->setHeaderData(custMod->fieldIndex("jun"), Qt::Horizontal, tr("6"));
    custMod->setHeaderData(custMod->fieldIndex("jul"), Qt::Horizontal, tr("7"));
    custMod->setHeaderData(custMod->fieldIndex("aug"), Qt::Horizontal, tr("8"));
    custMod->setHeaderData(custMod->fieldIndex("sep"), Qt::Horizontal, tr("9"));
    custMod->setHeaderData(custMod->fieldIndex("oct"), Qt::Horizontal, tr("10"));
    custMod->setHeaderData(custMod->fieldIndex("nov"), Qt::Horizontal, tr("11"));
    custMod->setHeaderData(custMod->fieldIndex("dec"), Qt::Horizontal, tr("12"));
    custMod->setHeaderData(custMod->fieldIndex("total"), Qt::Horizontal, tr("合计"));

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
    //ui->custTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->custTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Set column width
    ui->custTable->setColumnWidth(areaIdx,80);
    ui->custTable->setColumnWidth(cateIdx,80);
    ui->custTable->setColumnWidth(mainPepIdx,80);
    ui->custTable->setColumnWidth(posIdx,80);
    ui->custTable->setColumnWidth(custMod->fieldIndex("usr_name"),80);
    ui->custTable->setColumnWidth(genderIdx,40);
    ui->custTable->setColumnWidth(custMod->fieldIndex("relate_lev"),60);
    ui->custTable->setColumnWidth(custMod->fieldIndex("specialty"),80);
    ui->custTable->setColumnWidth(custMod->fieldIndex("in_time"),80);
    ui->custTable->setColumnWidth(custMod->fieldIndex("jan"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("feb"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("mar"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("apr"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("may"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("jun"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("jul"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("aug"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("sep"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("oct"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("nov"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("dec"),24);
    ui->custTable->setColumnWidth(custMod->fieldIndex("total"),40);
    ui->custTable->setColumnWidth(custMod->fieldIndex("birth_date"),80);
    ui->custTable->setColumnWidth(custMod->fieldIndex("contact"),90);
    ui->custTable->setColumnWidth(custMod->fieldIndex("unit_addr"),120);
    ui->custTable->setColumnWidth(custMod->fieldIndex("home_addr"),200);
    ui->custTable->setCurrentIndex(custMod->index (0, 0));
    //updateActions();
}

void CustWindow::showError(const QSqlError &err)
{
    QMessageBox::warning(this, tr("失败"),
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

        if (!ui->specEdit->text().trimmed().isEmpty())
        {
            //custMod->setFilter(tr("AND main_name LIKE '%") + ui->mainLevEdit->text().trimmed() + tr("%'"));
            queryStr = queryStr + tr(" AND specialty LIKE '%") + ui->specEdit->text().trimmed() + "%' ";
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
    //updateActions();
}

void CustWindow::changePassword()
{
    chgPwdDiag->clearText();
    chgPwdDiag->show();
    chgPwdDiag->exec();
}

void CustWindow::insertRow()
{
    custMod->setEditStrategy(QSqlTableModel::OnFieldChange);
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
    if (currentSelection.count() < 1)
    {
        QMessageBox::information(this,tr("提醒"),tr("请选择要删除的行"));
        return;
    }
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
    //updateActions();
}

void CustWindow::updateActions()
{
    if (ui->custTable->currentIndex().isValid())
    {
        ui->deleteRowAction->setDisabled(true);
    }
    else
    {
        ui->deleteRowAction->setDisabled(false);
    }
}

void CustWindow::about()
{
    QMessageBox::about(this, tr("关于"), tr("版权 2012 Vincent® 保留所有权利"));
}

CustWindow::~CustWindow()
{
    delete ui;
    delete custMod;
    delete chgPwdDiag;
}

