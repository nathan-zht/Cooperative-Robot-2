;; Auto-generated. Do not edit!


(when (boundp 'server_node::status)
  (if (not (find-package "SERVER_NODE"))
    (make-package "SERVER_NODE"))
  (shadow 'status (find-package "SERVER_NODE")))
(unless (find-package "SERVER_NODE::STATUS")
  (make-package "SERVER_NODE::STATUS"))

(in-package "ROS")
;;//! \htmlinclude status.msg.html


(defclass server_node::status
  :super ros::object
  :slots (_state _x_pos _y_pos ))

(defmethod server_node::status
  (:init
   (&key
    ((:state __state) 0)
    ((:x_pos __x_pos) 0)
    ((:y_pos __y_pos) 0)
    )
   (send-super :init)
   (setq _state (round __state))
   (setq _x_pos (round __x_pos))
   (setq _y_pos (round __y_pos))
   self)
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:x_pos
   (&optional __x_pos)
   (if __x_pos (setq _x_pos __x_pos)) _x_pos)
  (:y_pos
   (&optional __y_pos)
   (if __y_pos (setq _y_pos __y_pos)) _y_pos)
  (:serialization-length
   ()
   (+
    ;; int8 _state
    1
    ;; int8 _x_pos
    1
    ;; int8 _y_pos
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _state
       (write-byte _state s)
     ;; int8 _x_pos
       (write-byte _x_pos s)
     ;; int8 _y_pos
       (write-byte _y_pos s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _state
     (setq _state (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _state 127) (setq _state (- _state 256)))
   ;; int8 _x_pos
     (setq _x_pos (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _x_pos 127) (setq _x_pos (- _x_pos 256)))
   ;; int8 _y_pos
     (setq _y_pos (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _y_pos 127) (setq _y_pos (- _y_pos 256)))
   ;;
   self)
  )

(setf (get server_node::status :md5sum-) "6948d60b7d118ce47f95eddc739da798")
(setf (get server_node::status :datatype-) "server_node/status")
(setf (get server_node::status :definition-)
      "int8 state
int8 x_pos
int8 y_pos

")



(provide :server_node/status "6948d60b7d118ce47f95eddc739da798")


