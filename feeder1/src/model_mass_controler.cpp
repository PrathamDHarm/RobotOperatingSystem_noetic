#include "ros/callback_queue.h"
#include "ros/ros.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"
#include <functional>
#include <gazebo/common/common.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/transport/transport.hh>
#include <ignition/math/Vector3.hh>
#include <thread>

namespace gazebo {
class ModelMassControl : public ModelPlugin {
public:
  void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {


    if (_sdf->HasElement("name_link_to_change_mass"))
    {
      this->name_link_to_change_mass = _sdf->Get<std::string>("name_link_to_change_mass");
    }else
    {
      ROS_WARN("No link name given, setting default name %s",
             this->name_link_to_change_mass.c_str());
    }


    // Store the pointer to the model
    this->model = _parent;
    this->link_to_change_mass = this->model->GetLink(this->name_link_to_change_mass);


    // Listen to the update event. This event is broadcast every
    // simulation iteration.
    this->updateConnection = event::Events::ConnectWorldUpdateBegin(
        std::bind(&ModelMassControl::OnUpdate, this));


    // Create a topic name
    std::string model_mass_topicName = "/model_mass";

    // Initialize ros, if it has not already bee initialized.
    if (!ros::isInitialized()) {
      int argc = 0;
      char **argv = NULL;
      ros::init(argc, argv, "model_mas_controler_rosnode",
                ros::init_options::NoSigintHandler);
    }

    // Create our ROS node. This acts in a similar manner to
    // the Gazebo node
    this->rosNode.reset(new ros::NodeHandle("model_mas_controler_rosnode"));

    // Freq
    ros::SubscribeOptions so = ros::SubscribeOptions::create<std_msgs::Float32>(
        model_mass_topicName, 1,
        boost::bind(&ModelMassControl::OnRosMsg, this, _1), ros::VoidPtr(),
        &this->rosQueue);
    this->rosSub = this->rosNode->subscribe(so);

    // Spin up the queue helper thread.
    this->rosQueueThread =
        std::thread(std::bind(&ModelMassControl::QueueThread, this));
    
    ROS_WARN("Loaded ModelMassControl Plugin with parent...%s, Mass Controll Started ",
             this->model->GetName().c_str());
  }

  // Called by the world update start event
public:
  void OnUpdate() {
    ROS_DEBUG("Update Tick...");
  }

public:
  void SetMass(const double &_mass) {
    this->model_mass = _mass;
    // Changing the mass
    this->link_to_change_mass->GetInertial()->SetMass(this->model_mass);
    this->link_to_change_mass->UpdateMass();
    ROS_WARN("model_mass >> %f", this->model_mass);
  }

public:
  void OnRosMsg(const std_msgs::Float32ConstPtr &_msg) {
    this->SetMass(_msg->data);
  }

  /// \brief ROS helper function that processes messages
private:
  void QueueThread() {
    static const double timeout = 0.01;
    while (this->rosNode->ok()) {
      this->rosQueue.callAvailable(ros::WallDuration(timeout));
    }
  }


  // Pointer to the model
private:
  physics::ModelPtr model;

  // Pointer to the update event connection
private:
  event::ConnectionPtr updateConnection;


  // Mas of model
  double model_mass = 1.0;

  /// \brief A node use for ROS transport
private:
  std::unique_ptr<ros::NodeHandle> rosNode;

  /// \brief A ROS subscriber
private:
  ros::Subscriber rosSub;
  /// \brief A ROS callbackqueue that helps process messages
private:
  ros::CallbackQueue rosQueue;
  /// \brief A thread the keeps running the rosQueue
private:
  std::thread rosQueueThread;

  /// \brief A ROS subscriber
private:
  physics::LinkPtr link_to_change_mass;

private:
    std::string name_link_to_change_mass = "base_link";
};

// Register this plugin with the simulator
GZ_REGISTER_MODEL_PLUGIN(ModelMassControl)
} // namespace gazebo
