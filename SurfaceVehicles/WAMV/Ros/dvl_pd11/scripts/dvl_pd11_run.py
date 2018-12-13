#!/usr/bin/env python

'''

This is the script that should be used with rosrun to talk to the RDI DVL

Serial port parameters are manually set here but you may want to asign 
them using rospy.get_param for future use.

See dvl_pd11_driver.py for DVL serial string parsing. This driver will 
only work with the DVL set to PD11 ascii serial output mode.

'''

import serial
import rospy
import dvl_pd11_driver

if __name__ == '__main__':
    rospy.init_node('dvl', anonymous=False)
    ## serial port parameters
    s_port = '/dev/ttyUSB0'
    s_baud = '115200'

    try:
        #DVL = serial.Serial(port=s_port,baudrate=s_baud)
        dvl_driver = dvl_pd11_driver.DvlTalker()
        
        while not rospy.is_shutdown():
            ## read incoming serial strings 
            #line = DVL.readline()
            
            ## test strings - only uncomment for development
            #line = '$PRDIG,H,197.34,P,-10.2,R,-11.5,D,1.2*CHKSM'
            line = '$PRDIH,R,8.2,S,0.578,C,192.93*CHKSM'

            ## pass serial string to the parse/publish function
            dvl_driver.parse_pub(line)
            
            ## We can set timing here by uncommenting rate below. Otherwise the
            ## driver will run as quickly as it can. However, slowing down may
            ## cause us to miss some data.
            #rate = rospy.Rate(5) # 5hz
            #rate.sleep()
            
    except rospy.ROSInterruptException:
        DVL.close()
