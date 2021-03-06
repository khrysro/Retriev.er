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

#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QListWidgetItem>
#include <QDateTime>

namespace Ui {
    class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
	enum {
		RECUR_HOUR,
		RECUR_DAY,
		RECUR_WEEK,
		RECUR_MONTH
	};

	int		id;
	QString		from;
	QString		to;
	QString		title;

	QDateTime	opt_schedule;
	int             opt_recurrence;

	bool		opt_recursive;
	bool		opt_delete;
	bool		opt_remote;
	bool		opt_compress;
	bool		opt_show_progress;
	bool		opt_enable_schedule;

	explicit Task(QWidget *parent = 0);
	~Task();

	void createTask(void);
	void setId(int);
	int  getId(void);
	void setTitle(QString);
	void setFrom(QString);
	void setTo(QString);
	void setUseRemote(int);
	void setDelete(QString);
	void setCompress(QString);
	void setRecursive(int);
	void setShowProgress(QString);
	void setDateTime(QDateTime);
	void setEnableSchedule(bool);
	void setRecurrence(int);
	void sync(void);

public slots:
	void saveTask(void);
	QListWidgetItem * generateItem();
	void browseFrom(void);
	void browseTo(void);
	QString browse(void);
	void enableSchedule(bool checked);
	void setHourlyRecurrence(void);
	void setDailyRecurrence(void);
	void setWeeklyRecurrence(void);
	void setMontlyRecurrence(void);

signals:
	void signalChangedTask();

private:
	Ui::Task *ui;
	void setDestination(QString, QString);
};

#endif // TASK_H
