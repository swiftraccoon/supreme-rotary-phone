#include "../include/MP3TaggingService.h"

UploadService::UploadService(const std::string &endpoint,
                             const std::string &accessKey,
                             const std::string &secretKey,
                             const std::string &bucket)
    : bucketName(bucket)
{
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.endpointOverride = endpoint;
    clientConfig.scheme = Aws::Http::Scheme::HTTP;
    clientConfig.verifySSL = false;

    Aws::Auth::AWSCredentials credentials(accessKey, secretKey);
    s3Client = std::make_unique<Aws::S3::S3Client>(credentials, clientConfig);
}

UploadService::~UploadService()
{
    // No explicit clean-up needed here because the shutdown will be called elsewhere
}

void UploadService::uploadFile(const std::filesystem::path &localPath, const std::string &destPath)
{
    Aws::S3::Model::PutObjectRequest objectRequest;
    objectRequest.WithBucket(bucketName.c_str()).WithKey(destPath.c_str());

    auto input_data = std::make_shared<Aws::FStream>(localPath.c_str(),
                                                     std::ifstream::binary);
    objectRequest.SetBody(input_data);

    auto putObjectOutcome = s3Client->PutObject(objectRequest);

    if (!putObjectOutcome.IsSuccess())
    {
        std::cerr << "PutObject error: " << putObjectOutcome.GetError().GetExceptionName() << " " << putObjectOutcome.GetError().GetMessage() << std::endl;
    }
}