/*
 * Copyright (c) 2011, Leonardo Korndorfer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
**/
#include <QDebug>
#include <QFileDialog>
#include <QProcess>

#include "header/task.h"
#include "header/retriever.h"
#include "ui_task.h"

Task::Task(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Task)
{
	ui->setupUi(this);

	/**
	 * Connections
	 */
	connect(this->ui->taskButtonSave, SIGNAL(pressed()),
		this, SLOT(saveTask()));
	connect(this->ui->taskButtonCancel, SIGNAL(clicked()),
		this, SLOT(close()));
	connect(this->ui->buttonBrowseFrom, SIGNAL(clicked()),
		this, SLOT(browseFrom()));
	connect(this->ui->buttonBrowseTo, SIGNAL(clicked()),
		this, SLOT(browseTo()));

	/* schedule */
	connect(this->ui->scheduleEnable, SIGNAL(clicked(bool)),
		this, SLOT(enableSchedule(bool)));
	connect(this->ui->oncePerHour, SIGNAL(clicked()),
		this, SLOT(setHourlyRecurrence()));
	connect(this->ui->oncePerDay, SIGNAL(clicked()),
		this, SLOT(setDailyRecurrence()));
	connect(this->ui->oncePerWeek, SIGNAL(clicked()),
		this, SLOT(setWeeklyRecurrence()));
	connect(this->ui->oncePerMonth, SIGNAL(clicked()),
		this, SLOT(setMontlyRecurrence()));

	this->opt_recursive = false;
	this->opt_delete = false;
	this->opt_remote = false;
	this->opt_compress = false;
	this->opt_show_progress = false;
}

Task::~Task()
{
	delete ui;
}

void Task::createTask(void)
{
	return;
}

void Task::setId(int id)
{
	this->id = id;
	return;
}


int Task::getId(void)
{
	return this->id;
}

void Task::setTitle(QString s)
{
	this->title = s;
	this->ui->title->setText(s);
	return;
}

void Task::setFrom(QString s)
{
	this->from = s;
	this->ui->from->setText(s);
	return;
}

void Task::setTo(QString s)
{
	this->to = s;
	this->ui->to->setText(s);
	return;
}

void Task::setDateTime(QDateTime s)
{
	this->opt_schedule = s;
	this->ui->schedule->setDateTime(s);
	return;
}

void Task::setUseRemote(int n)
{
	int checked_state;
	this->opt_remote = n;
	checked_state = (n == 0)? Qt::Unchecked: Qt::Checked;
	this->ui->remote->setCheckState((Qt::CheckState)checked_state);

	qDebug() << this->opt_remote << "checked state";

	return;
}

void Task::setDelete(QString s)
{
	//this->opt_remote = s.toInt();
	return;
}

void Task::setCompress(QString s)
{
	//this->opt_remote = s.toInt();
	return;
}

void Task::setRecursive(int n)
{
	this->opt_recursive = n;
	int checked_state = (n == 0)? Qt::Unchecked: Qt::Checked;
	this->ui->recursive->setCheckState((Qt::CheckState)checked_state);
	return;
}

void Task::setShowProgress(QString s)
{
	//this->opt_remote = s.toInt();
	return;
}

void Task::setEnableSchedule(bool checked)
{
	if (checked == false)
	{
		this->ui->scheduleEnable->setChecked(false);
		this->ui->schedule->setEnabled(false);

		/* disable all recurrence radio */
		this->ui->oncePerHour->setEnabled(false);
		this->ui->oncePerDay->setEnabled(false);
		this->ui->oncePerWeek->setEnabled(false);
		this->ui->oncePerMonth->setEnabled(false);

		this->opt_enable_schedule = false;
	}
	else
	{
		this->ui->scheduleEnable->setChecked(true);
		this->ui->schedule->setEnabled(true);

		/* enable all recurrence radio */
		this->ui->oncePerHour->setEnabled(true);
		this->ui->oncePerDay->setEnabled(true);
		this->ui->oncePerWeek->setEnabled(true);
		this->ui->oncePerMonth->setEnabled(true);

		this->opt_enable_schedule = true;
	}
	return;
}

void Task::setHourlyRecurrence(void)
{
	qDebug() << "setHourlyRecurrence";
	this->setRecurrence(RECUR_HOUR);
	return;
}

void Task::setDailyRecurrence(void)
{
	qDebug() << "setDailyRecurrence";
	this->setRecurrence(RECUR_DAY);
	return;
}

void Task::setWeeklyRecurrence(void)
{
	qDebug() << "setWeeklyRecurrence";
	this->setRecurrence(RECUR_WEEK);
	return;
}

void Task::setMontlyRecurrence(void)
{
	qDebug() << "setMontlyRecurrence";
	this->setRecurrence(RECUR_MONTH);
	return;
}

void Task::setRecurrence(int b)
{
	qDebug() << "button " << b;
	switch (b)
	{
		case RECUR_HOUR:
			this->ui->oncePerHour->setChecked(true);
			break;
		case RECUR_DAY:
			this->ui->oncePerDay->setChecked(true);
			break;
		case RECUR_WEEK:
			this->ui->oncePerWeek->setChecked(true);
			break;
		case RECUR_MONTH:
			this->ui->oncePerMonth->setChecked(true);
			break;
		default:
			qCritical() << "Not known option";
			return;
	}
	this->opt_recurrence = b;

	return;
}

void Task::enableSchedule(bool checked)
{
	this->setEnableSchedule(checked);
}

void Task::browseFrom(void){this->ui->from->setText(this->browse());}

void Task::browseTo(void)  {this->ui->to->setText(this->browse());}

QString Task::browse(void)
{
	QString directory = QDir::toNativeSeparators(
		QFileDialog::getExistingDirectory(this,
		tr("Find Files"), QDir::homePath())
	);
	qDebug() << directory;

	return directory;
}

void Task::saveTask(void)
{
	if (this->ui->title->text().size() < 1)
	{
		this->close();
		delete(this);
		return;
	}

	this->title    = this->ui->title->text();
	this->from     = this->ui->from->text();
	this->to       = this->ui->to->text();
	this->opt_recursive = this->ui->recursive->isChecked();
	this->opt_remote = this->ui->remote->isChecked();
	this->opt_schedule = this->ui->schedule->dateTime();

	qDebug() << this->opt_schedule.toString();

	this->close();
	emit this->signalChangedTask();

	return;
}

QListWidgetItem * Task::generateItem()
{
	QListWidgetItem *item = new QListWidgetItem(this->title);
	return item;
}
