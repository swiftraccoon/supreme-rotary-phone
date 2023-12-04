#ifndef UPLOADSERVICE_H
#define UPLOADSERVICE_H

#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <string>
#include <filesystem>
#include <memory>

class UploadService
{
private:
    std::unique_ptr<Aws::S3::S3Client> s3Client;
    std::string bucketName;

public:
    UploadService(const std::string &endpoint,
                  const std::string &accessKey,
                  const std::string &secretKey,
                  const std::string &bucket);
    ~UploadService();

    void uploadFile(const std::filesystem::path &localPath, const std::string &destPath);
};

#endif // UPLOADSERVICE_H