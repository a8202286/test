#! /usr/bin/env python3
# -*- coding: utf-8 -*-
'''
      Copyright 2019,王思远 <darknightghost.cn@gmail.com>
      This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
      You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
'''

import PyQt5
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

import Station
import Common
from Common import *

import WorkSpaceWidget
from WorkSpaceWidget.ModulesItem import *
from WorkSpaceWidget.SummaryItem import *


class WorkSpaceWidget(QTreeWidget):
    '''
        Workspace.
    '''
    updateData = pyqtSignal()

    @TypeChecker(QTreeWidget, QMainWindow, Station.Station)
    def __init__(self, parent, station):
        super().__init__(parent)
        self.__station = station
        self.header().setVisible(False)

        self.__modulesItem = ModulesItem(self)
        self.updateData.connect(self.__modulesItem.onUpdateData)
        self.addTopLevelItem(self.__modulesItem)

        self.__summaryItem = SummaryItem(self)
        self.updateData.connect(self.__summaryItem.onUpdateData)
        self.addTopLevelItem(self.__summaryItem)

        self.updateData.connect(self.__onUpdateData)
        self.updateData.emit()

    def __onUpdateData(self):
        '''
            Update data.
        '''
        self.setWindowTitle(self.__station.name())
