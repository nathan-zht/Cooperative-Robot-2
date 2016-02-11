;; Auto-generated. Do not edit!


(when (boundp 'driver_node::driver_setting)
  (if (not (find-package "DRIVER_NODE"))
    (make-package "DRIVER_NODE"))
  (shadow 'driver_setting (find-package "DRIVER_NODE")))
(unless (find-package "DRIVER_NODE::DRIVER_SETTING")
  (make-package "DRIVER_NODE::DRIVER_SETTING"))

(in-package "ROS")
;;//! \htmlinclude driver_setting.msg.html


(defclass driver_node::driver_setting
  :super ros::object
  :slots (_period _duty _wheel ))

(defmethod driver_node::driver_setting
  (:init
   (&key
    ((:period __period) 0)
    ((:duty __duty) 0)
    ((:wheel __wheel) 0)
    )
   (send-super :init)
   (setq _period (round __period))
   (setq _duty (round __duty))
   (setq _wheel (round __wheel))
   self)
  (:period
   (&optional __period)
   (if __period (setq _period __period)) _period)
  (:duty
   (&optional __duty)
   (if __duty (setq _duty __duty)) _duty)
  (:wheel
   (&optional __wheel)
   (if __wheel (setq _wheel __wheel)) _wheel)
  (:serialization-length
   ()
   (+
    ;; int32 _period
    4
    ;; int8 _duty
    1
    ;; int8 _wheel
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _period
       (write-long _period s)
     ;; int8 _duty
       (write-byte _duty s)
     ;; int8 _wheel
       (write-byte _wheel s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _period
     (setq _period (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int8 _duty
     (setq _duty (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _duty 127) (setq _duty (- _duty 256)))
   ;; int8 _wheel
     (setq _wheel (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _wheel 127) (setq _wheel (- _wheel 256)))
   ;;
   self)
  )

(setf (get driver_node::driver_setting :md5sum-) "6697fb50f4e483911cb6c8595601db97")
(setf (get driver_node::driver_setting :datatype-) "driver_node/driver_setting")
(setf (get driver_node::driver_setting :definition-)
      "int32 period
int8 duty
int8 wheel

")



(provide :driver_node/driver_setting "6697fb50f4e483911cb6c8595601db97")


