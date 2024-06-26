cmake_minimum_required(VERSION 3.5)

project(Hospital LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets PrintSupport Network REQUIRED)

set(SRC  pages/dialogs/login/loginpage.h
         pages/dialogs/login/loginpage.cpp
         pages/dialogs/login/loginpage.ui

         utils/windowframelesshelper.h
         utils/windowframelesshelper.cpp
         utils/inputtester.h
         utils/printhelp.h
         utils/printhelp.cpp
         utils/findposhelper.h
         utils/findposhelper.cpp
         utils/nethelp.h
         utils/nethelp.cpp
         utils/singleton.h

	
         pages/basedialog/basedialog.h
         pages/basedialog/basedialog.cpp
         pages/basedialog/basedialog.ui
	
         pages/dialogs/datepick/datepickerpopup.h
         pages/dialogs/datepick/datepickerpopup.cpp
         pages/dialogs/datepick/datepickerpopup.ui
	
         pages/dialogs/messagedlg/messagedlg.h
         pages/dialogs/messagedlg/messagedlg.cpp
         pages/dialogs/messagedlg/messagedlg.ui
	
         pages/dialogs/messagedlg/messagepopdlg.h
         pages/dialogs/messagedlg/messagepopdlg.cpp
         pages/dialogs/messagedlg/messagepopdlg.ui
	
         pages/dialogs/messagedlg/progressbardlg.h
         pages/dialogs/messagedlg/progressbardlg.cpp
         pages/dialogs/messagedlg/progressbardlg.ui

         pages/dialogs/search/searchdlg.h
         pages/dialogs/search/searchdlg.cpp
         pages/dialogs/search/searchdlg.ui

         pages/outpatientservice/outpatientservice.h
         pages/outpatientservice/outpatientservice.cpp
         pages/outpatientservice/outpatientservice.ui
         pages/outpatientservice/recorddialog.h
         pages/outpatientservice/recorddialog.cpp
         pages/outpatientservice/alarmingrecorddialog.ui

         pages/outpatientservice/pages/checkitempage/checkitempage.h
         pages/outpatientservice/pages/checkitempage/checkitempage.cpp
         pages/outpatientservice/pages/checkitempage/checkitempage.ui
         pages/outpatientservice/pages/checkitempage/widgets/checkitem.h
         pages/outpatientservice/pages/checkitempage/widgets/checkitem.cpp
         pages/outpatientservice/pages/checkitempage/widgets/checkitem.ui
         pages/outpatientservice/pages/checkitempage/dialogs/checkselectdlg.h
         pages/outpatientservice/pages/checkitempage/dialogs/checkselectdlg.cpp
         pages/outpatientservice/pages/checkitempage/dialogs/bodycheckpage.h
         pages/outpatientservice/pages/checkitempage/dialogs/bodycheckpage.cpp
         pages/outpatientservice/pages/checkitempage/dialogs/imagecheckpage.h
         pages/outpatientservice/pages/checkitempage/dialogs/imagecheckpage.cpp
         pages/outpatientservice/pages/checkitempage/dialogs/laboratorycheckpage.h
         pages/outpatientservice/pages/checkitempage/dialogs/laboratorycheckpage.cpp
         pages/outpatientservice/pages/checkitempage/dialogs/othercheckpage.h
         pages/outpatientservice/pages/checkitempage/dialogs/othercheckpage.cpp
         pages/outpatientservice/pages/checkitempage/dialogs/defaultpage.h
         pages/outpatientservice/pages/checkitempage/dialogs/defaultpage.cpp
         pages/outpatientservice/pages/checkitempage/dialogs/defaultpage.ui
         pages/outpatientservice/pages/dealpage/dealpage.h
         pages/outpatientservice/pages/dealpage/dealpage.cpp
         pages/outpatientservice/pages/dealpage/dealpage.ui

         pages/outpatientservice/pages/medicinepage/medicinepage.h
         pages/outpatientservice/pages/medicinepage/medicinepage.cpp
         pages/outpatientservice/pages/medicinepage/medicinepage.ui
         pages/outpatientservice/pages/medicinepage/widgets/medicinewidget.h
         pages/outpatientservice/pages/medicinepage/widgets/medicinewidget.cpp
         pages/outpatientservice/pages/medicinepage/widgets/medicinewidget.ui

         pages/outpatientservice/pages/recordpage/recordpage.h
         pages/outpatientservice/pages/recordpage/recordpage.cpp
         pages/outpatientservice/pages/recordpage/recordpage.ui


         widgets/messagehint/messagehint.h
         widgets/messagehint/messagehint.cpp
         widgets/customtableview/customtableview.h
         widgets/customtableview/customtableview.cpp
         widgets/customtableview/headerdelegate.h
         widgets/customtableview/headerdelegate.cpp
         widgets/customtableview/tableviewdelegate.h
         widgets/customtableview/tableviewdelegate.cpp

         pages/doctor/mainpage.h
         pages/doctor/mainpage.cpp
         pages/doctor/mainpage.ui

         pages/doctor/pages/patientselect/patientselect.h
         pages/doctor/pages/patientselect/patientselect.cpp
         pages/doctor/pages/patientselect/patientselect.ui
         pages/doctor/pages/patientrecord/patientrecord.h
         pages/doctor/pages/patientrecord/patientrecord.cpp
         pages/doctor/pages/patientrecord/patientrecord.ui
         pages/doctor/pages/doctorword/doctorword.h
         pages/doctor/pages/doctorword/doctorword.cpp
         pages/doctor/pages/doctorword/doctorword.ui
         pages/doctor/pages/bedmanage/bedmanage.h
         pages/doctor/pages/bedmanage/bedmanage.cpp
         pages/doctor/pages/bedmanage/bedmanage.ui
)

add_executable(Hospital
    main.cpp
    app.cpp
    app.h
    app.ui
    app.qrc
    appsetting.h

    ${SRC}
  )

target_link_libraries(Hospital PRIVATE Qt5::Widgets Qt5::PrintSupport Qt5::Network)

