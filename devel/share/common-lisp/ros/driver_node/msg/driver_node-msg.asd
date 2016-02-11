
(cl:in-package :asdf)

(defsystem "driver_node-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "driver_setting" :depends-on ("_package_driver_setting"))
    (:file "_package_driver_setting" :depends-on ("_package"))
  ))