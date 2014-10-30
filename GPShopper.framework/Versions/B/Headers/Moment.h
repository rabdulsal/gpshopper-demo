//
//  TNFMoment.h
//  northface
//
//  Created by Patrick Caraher on 8/28/12.
//  Copyright (c) 2012 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MomentAcceptanceState.h"

#define kMomentSeparator @","

#define kMomentMomentID @"id"
#define kMomentMomentIDs @"moment_ids"
#define kMomentTitle @"title"
#define kMomentLocation @"location"
#define kMomentImageName @"imageName"
#define kMomentSubmitDate @"submit_date"
#define kMomentUserProfileId @"user_profile_id"
#define kMomentAcceptanceStateId @"acceptanceStateId"
#define kMomentImageData @"image_data"
#define kMomentProductIds @"grpids"
#define kMomentProductInfo @"productInfo"

@interface Moment : NSObject
{
@private
    NSArray *_productInfos;
}

- (id)initWithDict:(NSDictionary *)dict;

@property (nonatomic, copy) NSString *momentId;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *location;
@property (nonatomic, copy) NSString *imageName;
@property (nonatomic, retain) NSDate *submitDate;
@property (nonatomic, copy) NSNumber *userProfileId;
@property (nonatomic, retain) MomentAcceptanceState *acceptanceState;
@property (nonatomic, copy) NSData *imageData;
@property (nonatomic, copy) NSSet *productIds;

- (NSString *)base64EncodedImage;
- (NSString *)productIdList;
- (void)addProductId:(NSNumber *)productId;
- (void)removeProductId:(NSNumber *)productId;
- (void)setProductIdsFromProducts:(NSSet *)products;

- (BOOL)isAccepted;
- (BOOL)isFeatured;
- (BOOL)isRejected;
- (BOOL)isSubmitted;

- (NSArray *)orderedProductIds;
- (NSArray *)productInfos;
- (NSArray *)validationErrors;

@end
