import time
import serial
from jenkinsapi.jenkins import Jenkins


class JenkinsConnection:
    def __init__(self, server='<URI of Jenkins server>'):
        self.jenkins_server = Jenkins(server)
        self.jenkins_job = self.jenkins_server['stumps-hackathon-CILights']
        self.current_status = ''
        self.start_polling()

    def start_polling(self):
        while True:
            time.sleep(5)
            is_building = self.jenkins_job.is_queued_or_running()
            if is_building:
                jenkins_build_status = 'RUNNING'
            else:
                jenkins_build_status = self.jenkins_job.get_last_build().get_status()
            if jenkins_build_status != self.current_status:
                self.current_status = jenkins_build_status
                self.send_arduino(self.current_status)

    @staticmethod
    def send_arduino(current_status):
        ser = serial.Serial('COM3', 9600)
        time.sleep(2)

        if current_status == 'RUNNING':
            print('Running')
            ser.write('0')
        elif current_status == 'SUCCESS':
            ser.write('1')
            print('SUCCESS')
        else:
            print('FAILURE')
            ser.write('2')


if __name__ == '__main__':
    JenkinsConnection()
