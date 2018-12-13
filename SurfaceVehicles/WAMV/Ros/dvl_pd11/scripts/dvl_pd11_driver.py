#!/usr/bin/env python

'''

This module takes care of parsing DVL serial strings and then 
publishing velocities to the TwistStamped message type and all 
other DVL data to the custom NMEA_PD11 message type.

To run the driver and set the serial port parameters see:
dvl_pd11_run.py

'''

import logging
# using built in logging module for protyping but can later be replaced with rospy logging

import serial
import rospy
#from std_msgs.msg import String
from dvl_pd11.msg import NMEA_PD11
from geometry_msgs.msg import TwistStamped


class DvlTalker(object):
    def __init__(self):
        self.vel_pub = rospy.Publisher('vel', TwistStamped, queue_size=1)
        self.dvl_PRDIH_pub = rospy.Publisher('dvl_PRDIH', NMEA_PD11, queue_size=1)
        self.dvl_PRDIG_pub = rospy.Publisher('dvl_PRDIG', NMEA_PD11, queue_size=1)

    def parse_pub(self,line):
        aa = line.split(',')
        if len(aa) == 7:
            if aa[0] == '$PRDIH':
                try:
                    current_time = rospy.get_rostime()
                    frame_id = '0' # 0=no frame, 1=global frame ; import this value?
                    rtb = float(aa[2])
                    sog = float(aa[4])
                    
                    vel_msg = TwistStamped()
                    vel_msg.twist.linear.x = sog # assuming x is forward
                    vel_msg.twist.linear.y = 0.0 # don't have lateral DVL velocity with PD11 mode
                    vel_msg.header.stamp = current_time
                    vel_msg.header.frame_id = frame_id
                    self.vel_pub.publish(vel_msg)
                    
                    dvl_PRDIH_msg = NMEA_PD11()
                    dvl_PRDIH_msg.rtb = rtb
                    dvl_PRDIH_msg.sog = sog
                    self.dvl_PRDIH_pub.publish(dvl_PRDIH_msg)
                    
                except ValueError:
                    logging.warning("Problem converting fields to float values")
            else:
                logging.debug('Not the correct NMEA string')
                
        elif len(aa) ==9:
            if aa[0] == '$PRDIG':
                try:
                    hdg = float(aa[2])
                    pitch = float(aa[4])
                    roll = float(aa[6])
                    
                    dvl_PRDIG_msg = NMEA_PD11()
                    dvl_PRDIG_msg.hdg = hdg
                    dvl_PRDIG_msg.pitch = pitch
                    dvl_PRDIG_msg.roll = roll
                    self.dvl_PRDIG_pub.publish(dvl_PRDIG_msg)
                    
                except ValueError:
                    logging.warning("Problem converting fields to float values")
            else:
                logging.debug('Not the correct NMEA string')
        else:
            logging.debug('Not an identifiable NMEA string')

            


