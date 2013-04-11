QT += widgets

TEMPLATE      = \
              subdirs
SUBDIRS       = \
		2dprimitives \
		xgxperfserver \
             automationlib \
              widgetlib \
		autoscreenlib \
		ecgmonitorlib \
		vslib \
              applicationmanager/xgxperf_app \
		applicationmanager/xgxperf_launcher \
		xgxperftemplatelib

embedded {
	SUBDIRS += livemem
}

contains(QT_CONFIG, webkit): SUBDIRS += browserlib

contains(QT_CONFIG, opengles2): SUBDIRS += glwidgetlib 

