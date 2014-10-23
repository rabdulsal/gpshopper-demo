//
//  GPDPDPViewController.m
//  GPSDemo
//
//  Created by James Lee on 5/14/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDPDPViewController.h"
#import "GPDImageFetcher.h"

@interface GPDPDPViewController ()
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UILabel *detailLabel;
@property (weak, nonatomic) IBOutlet UILabel *priceLabel;
@property (strong, nonatomic) SCLocalizedProductFetcher *productFetcher;

@end

@implementation GPDPDPViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self reloadAll];
    
    self.productFetcher = [[SCLocalizedProductFetcher alloc] initWithListener:self];
    if (self.grpid) {
        [self.productFetcher fetchLocalizedProductForGrpid:self.grpid zipcode:@"USEGPS"];
    } else if (self.product) {
        [self.productFetcher fetchLocalizedProductForGrpid:self.product.grpid zipcode:@"USEGPS"];
    }
}


- (void)reloadAll
{
    id<SCBaseProduct> product = self.localInstance ? self.localInstance : self.product;
    
    
    NSString *url = [product urlForImageWithinSize:CGSizeMake(640, 640)];
    UIImage *cachedImage = [[GPDImageFetcher sharedInstance] cachedImageForURL:url];
    if (cachedImage) {
        self.imageView.image = cachedImage;
    } else {
        [[GPDImageFetcher sharedInstance] fetchImageForURL:url cache:YES completion:^(UIImage *image) {
            self.imageView.image = cachedImage;
        }];
    }
    self.titleLabel.text = product.productName ? product.productName : @"";
    self.detailLabel.text = [NSString stringWithFormat:@"%@\n\n%@",
                             product.shortDescription ? product.shortDescription : @"",
                             product.longDescription ? product.longDescription : @""];
    
    
    InstanceSpecificInfo *firstInstance = self.localInstance ? [self.localInstance.nearbyInstances firstObject] : [self.product.productInstances firstObject];
    NSNumber *price = [NSNumber numberWithUnsignedLongLong:firstInstance.price/100.f];
    NSString *priceString = [NSString stringWithFormat:@"%@",
                            [NSNumberFormatter localizedStringFromNumber:price numberStyle:NSNumberFormatterCurrencyStyle]];
    self.priceLabel.text = priceString ? priceString : @"";
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark SCLocalizedProductFetcherListener
-(void)scLocalizedProductFetcher: (SCLocalizedProductFetcher *)f
                  fetchedProduct: (SCLocalizedProduct *)p
{
    self.localInstance = p;
    dispatch_async(dispatch_get_main_queue(), ^{
        [self reloadAll];
    });

}

-(void)scLocalizedProductFetcherFailed: (SCLocalizedProductFetcher *)f {}


+ (void)initialize
{
    NSArray *ri_image_sizes = @[@[@480,@640]];
    [SCLocalizedProductFetcher setImageSizes:ri_image_sizes];
}
@end
