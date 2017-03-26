#include "qcalwidget.h"

static ViSession defaultRM;
static ViSession instr;
static ViStatus status;
static ViUInt32 retCount;
static ViUInt32 writeCount;
static unsigned char buffer[100];
static char stringinput[512];



QCALWidget::QCALWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QCALWidget)
{
    ui->setupUi(this);

    /*
     * First we must call viOpenDefaultRM to get the resource manager
     * handle.  We will store this handle in defaultRM.
     */
   status=viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)
   {
      qDebug () << "Could not open a session to the VISA Resource Manager!\n";
      exit (EXIT_FAILURE);
   }

   status = viOpen (defaultRM, (ViRsrc) "GPIB0::18::INSTR", VI_NULL, VI_NULL, &instr);
   if (status < VI_SUCCESS)
   {
        qDebug () << "Cannot open a session to the device.\n";
        return;
   }
   qDebug () << "Open a session to the device success.\n";

    /*
     * Set timeout value to 5000 milliseconds (5 seconds).
     */
   status = viSetAttribute (instr, VI_ATTR_TMO_VALUE, 5000);




}

QCALWidget::~QCALWidget()
{
    delete ui;
}

void QCALWidget::on_pushButtonQCALScan_released()
{

}

void QCALWidget::on_pushButtonQCALConnect_released()
{
    /*
     * At this point we now have a session open to the instrument at
     * Primary Address 2.  We can use this session handle to write
     * an ASCII command to the instrument.  We will use the viWrite function
     * to send the string "*IDN?", asking for the device's identification.
     */
   //strcpy(stringinput,"*IDN?");
   strcpy(stringinput,"FUNC SIN;:VOLT 100;:FREQ 50");
   status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
   if (status < VI_SUCCESS)
   {
      qDebug () << "Error writing to the device\n";
      return;
   }

    /*
     * Now we will attempt to read back a response from the device to
     * the identification query that was sent.  We will use the viRead
     * function to acquire the data.  We will try to read back 100 bytes.
     * After the data has been read the response is displayed.
     */
   status = viRead (instr, buffer, 100, &retCount);
   if (status < VI_SUCCESS)
   {
      qDebug () << "Error reading a response from the device\n";
   }
   qDebug () << buffer;
}
