#include <ntddk.h>
#include <wdf.h>

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KmdfHelloWorldEvtDeviceAdd;

NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT		DriverObject,
	_In_ PUNICODE_STRING	RegistryPath
)
{
	//NTSTATUS variable to record success or failure
	NTSTATUS status = STATUS_SUCCESS;

	//Allocate driver confuguration object
	WDF_DRIVER_CONFIG config;

	//Print "Hello World" for DriverEntry"
	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: DriverEntry\n"));

	//Initialize driver configuration object to register
	//engry point for EvtDeviceAdd callback, KmdfHelloWorldEvtDeviceAdd
	WDF_DRIVER_CONFIG_INIT(&config,
		KmdfHelloWorldEvtDeviceAdd
	);
	//Create driver object
	status = WdfDriverCreate(DriverObject, 
		RegistryPath,
		WDF_NO_OBJECT_ATTRIBUTES,
		&config,
		WDF_NO_HANDLE
	);
	return status;
}
NTSTATUS
KmdfHelloWorldEvtDeviceAdd(
	_In_	WDFDRIVER		Driver,
	_Inout_	PWDFDEVICE_INIT	DeviceInit
)
{
	//No driver object, so it is marked as unreferenced
	UNREFERENCED_PARAMETER(Driver);

	NTSTATUS status;

	//Allocate driver object
	WDFDEVICE hDevice;

	//Print our message
	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: KmdfHelloWorldEvtDeviceAdd\n"));
	KdPrint(("This is driver entry \r\n"));

	//Create Device Object
	status = WdfDeviceCreate(&DeviceInit,
		WDF_NO_OBJECT_ATTRIBUTES,
		&hDevice
	);
	return status;

	
}