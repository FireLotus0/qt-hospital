#pragma once

#include "utils/singleton.h"

#include <QString>
#include <QObject>

struct User{
    int id = -1;
    QString name = "";
    QString passwd = "";
    QString department = "";
};


struct PatientInfo
{
   QString s_patient_id;
   QString s_expense_source;
   QString s_insurance_id;
   int s_doctor_id;
   int s_type;
   QString s_patient_name;
   int s_age;
   QString s_patient_sex;
   QString s_addr;
   QString s_phone;
   QString s_job;
   QString s_id_type;
   QString s_date;
   QString s_main_suit;
   QString s_present_illness;
   QString s_body_check;
   QString s_blood_pressure;
   QString s_empty_blood_glucose;
   QString s_meal_blood_glucose;
   QString s_help_check;
   QString s_first_diagnose;
   QString s_deal;
   QString s_doctor_name;
   QString s_make_date;
   QString s_department;
};

struct CheckProject
{
    QString s_project_id = "";		      // 项目编码
    QString s_patient_id = "";          // 病人ID
    QString s_note = "";                // 备注
    QString s_doctor_name = "";         // 医师
    QString s_department = "";				// 科室
    QString s_check_part = "";				// 检查部位
    QString s_goal = "";					// 检查目的
    QString s_project_name = "";			// 项目名称
    QString s_project_name_f = "";			// 收费项目名称
    QString s_project_size = "";				// 项目规格
    double s_price = 0.0;					   // 价格
    int s_num = 0;				   // 数量
    double s_total = 0.0;					// 金额
};
Q_DECLARE_METATYPE(CheckProject)

struct Medicine {
   QString s_medicine_id;
   QString s_name;
   QString s_bar_code ;
   QString s_size;
   QString s_unit;
   QString s_manufacturer;
   QString s_approval_number;
   double s_price;
   QString s_pharmacy;
   QString s_tabu;
   QString s_adaptation_disease;
   QString s_adverse_reaction;
   QString s_special_note;
   QString s_note;
   int s_prescription_type;		// 处方类型
   int s_skin_test;				// 皮试结果
   int s_medical_type;				// 药品类型
};


using CurDoctor = Singleton<User>;
using CurPatient = Singleton<PatientInfo>;



