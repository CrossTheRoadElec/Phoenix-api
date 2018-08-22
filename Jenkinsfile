pipeline {
    agent none
    stages {
        stage('build athena') {
            agent { docker { image 'ctre/linuxbase' } }
            steps {
                sh './gradlew build --no-daemon -PonlyAthena -PnoCopy -PjenkinsBuild-PreleaseBuild --console=plain --stacktrace --refresh-dependencies'
            }
        }

        stage('build linux') {
            agent { docker { image 'ctre/linuxbase' } }
            steps {
                sh './gradlew build --no-daemon -PskipAthena -PnoCopy -PjenkinsBuild -PreleaseBuild --console=plain --stacktrace --refresh-dependencies'
            }
        }
        
        stage('build windows') {
            agent {
                node {
                    label 'master'
                }
            } 
            environment {
                DOCKER_TLS_VERIFY="1"
                DOCKER_HOST="tcp://192.168.99.90:2376"
                DOCKER_CERT_PATH="/home/admin/.docker/machine/machines/2016"
                DOCKER_MACHINE_NAME="2016"
            }   
            steps {
                //Run the VM. If it is already up, this will do nothing. This has an exclusive lock that waits for access
                sh 'sh -c \'sudo /home/admin/windows-docker-machine/vagrant-up.sh\''
                sh 'docker pull ctre/windowsbase'
                sh '''if [ "$(docker ps -q -f name=visualstudio1)" ]; then
                        docker kill visualstudio1 
                        #labeled 1 to allow for running in parallel
                        docker rm visualstudio1
                    else
                        if [ "$(docker ps -aq -f status=exited -f name=visualstudio1)" ]; then
                            # cleanup
                            docker rm visualstudio1
                        fi
                    fi
                    # run your container
                    target_dir=/home/admin$PWD
                    docker run -it -d --name visualstudio1 -v C:$target_dir:C:/build_dir -w C:/build_dir ctre/windowsbase
                    '''
                sh '''docker exec visualstudio1 powershell ./gradlew build --no-daemon -PjenkinsBuild -PnoCopy -PreleaseBuild --console=plain --stacktrace --refresh-dependencies'''
            }
        }
    }
}
