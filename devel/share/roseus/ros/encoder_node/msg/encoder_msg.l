;; Auto-generated. Do not edit!


(when (boundp 'encoder_node::encoder_msg)
  (if (not (find-package "ENCODER_NODE"))
    (make-package "ENCODER_NODE"))
  (shadow 'encoder_msg (find-package "ENCODER_NODE")))
(unless (find-package "ENCODER_NODE::ENCODER_MSG")
  (make-package "ENCODER_NODE::ENCODER_MSG"))

(in-package "ROS")
;;//! \htmlinclude encoder_msg.msg.html


(defclass encoder_node::encoder_msg
  :super ros::object
  :slots (_ticks _direction ))

(defmethod encoder_node::encoder_msg
  (:init
   (&key
    ((:ticks __ticks) 0)
    ((:direction __direction) 0)
    )
   (send-super :init)
   (setq _ticks (round __ticks))
   (setq _direction (round __direction))
   self)
  (:ticks
   (&optional __ticks)
   (if __ticks (setq _ticks __ticks)) _ticks)
  (:direction
   (&optional __direction)
   (if __direction (setq _direction __direction)) _direction)
  (:serialization-length
   ()
   (+
    ;; int32 _ticks
    4
    ;; int8 _direction
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _ticks
       (write-long _ticks s)
     ;; int8 _direction
       (write-byte _direction s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _ticks
     (setq _ticks (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int8 _direction
     (setq _direction (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _direction 127) (setq _direction (- _direction 256)))
   ;;
   self)
  )

(setf (get encoder_node::encoder_msg :md5sum-) "4e36c3dcce149655ed1ec27c09a76291")
(setf (get encoder_node::encoder_msg :datatype-) "encoder_node/encoder_msg")
(setf (get encoder_node::encoder_msg :definition-)
      "int32 ticks
int8  direction

")



(provide :encoder_node/encoder_msg "4e36c3dcce149655ed1ec27c09a76291")


