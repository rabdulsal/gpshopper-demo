//
//  GPDHomeViewController.m
//  GPSDemo
//
//  Created by James Lee on 5/2/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDHomeViewController.h"
#import "TWTSideMenuViewController.h"

@interface GPDHomeViewController ()
@property (strong, nonatomic) IBOutlet BannerView *banner1;
@property (strong, nonatomic) IBOutlet SCBannerScrollView *banner2;
@property (strong, nonatomic) IBOutlet BannerView *banner3;
@end

@implementation GPDHomeViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    SCBannerScrollViewConfig *config = [[SCBannerScrollViewConfig alloc] initWithPositionName:@"home_large_banner"];
    self.banner1.bannerName = @"home_small_banner";
    self.banner2.config = config;
    self.banner3.bannerName = @"home_bottom_banner";
}
@end
