#pragma once
#include <fstream>
#include <CL/opencl.hpp>
#include <vector>
class OpenCl
{
public:
    OpenCl() { init(); }
	
    void printInfo();
    cl::Context getContext() { return this->mContext; };
    cl::Program::Sources getSources() { return this->mSources; }
private:
    void init();
    void get_default_device();

    std::vector<cl::Platform> mAllPlatforms;
    cl::Platform mDefaultPlatform;
    std::vector<cl::Device> mAllDevices;
    cl::Device mDefaultDevice;
    cl::Context mContext;
    cl::Program::Sources mSources;
};

void OpenCl::init() {
    this->mContext = cl::Context(this->mDefaultDevice);
}
void OpenCl::printInfo() {
    auto device = this->mDefaultDevice;
    auto name = device.getInfo<CL_DEVICE_NAME>();
    auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
    auto version = device.getInfo<CL_DEVICE_VERSION>();
    auto workItems = device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
    auto workGroups = device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
    auto computeUnits = device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
    auto globalMemory = device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
    auto localMemory = device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>();

    std::cout << "OpenCL Device Info:"
        << "\nName: " << name
        << "\nVendor: " << vendor
        << "\nVersion: " << version
        << "\nMax size of work-items: (" << workItems[0] << "," << workItems[1] << "," << workItems[2] << ")"
        << "\nMax size of work-groups: " << workGroups
        << "\nNumber of compute units: " << computeUnits
        << "\nGlobal memory size (bytes): " << globalMemory
        << "\nLocal memory size per compute unit (bytes): " << localMemory / computeUnits
        << std::endl;
}

void OpenCl::get_default_device() {

    //get all platforms (drivers)
    cl::Platform::get(&this->mAllPlatforms);
    if (this->mAllPlatforms.size() == 0) {
        std::cout << " No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    this->mDefaultPlatform = this->mAllPlatforms[0];
    std::cout << "Using platform: " << this->mDefaultPlatform.getInfo<CL_PLATFORM_NAME>() << "\n";
    //get default device of the default platform
    
    this->mDefaultPlatform.getDevices(CL_DEVICE_TYPE_ALL, &this->mAllDevices);
    if (this->mAllDevices.size() == 0) {
        std::cout << " No devices found. Check OpenCL installation!\n";
        exit(1);
    }
    this->mDefaultDevice = this->mAllDevices[0];

    std::cout << "Using device: " << this->mDefaultDevice.getInfo<CL_DEVICE_NAME>() << "\n";

}